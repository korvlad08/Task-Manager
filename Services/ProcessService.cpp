#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <sddl.h>
#include <vector>

#include "ProcessService.h"

#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "advapi32.lib")

ProcessService::ProcessService()
{
    prevCpuTime = gcnew Dictionary<int, TimeSpan>();
    suspendedProcesses = gcnew List<int>();
    partiallySuspended = gcnew List<int>();
    lastUpdate = DateTime::Now;
};

List<ProcessInfo^>^ ProcessService::GetProcesses()
{
    List<ProcessInfo^>^ result = gcnew List<ProcessInfo^>();
    Dictionary<int, TimeSpan>^ newCpu = gcnew Dictionary<int, TimeSpan>();

    DateTime now = DateTime::Now;
    double elapsedMs = (now - lastUpdate).TotalMilliseconds;
    lastUpdate = now;

    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE)
    {
        return result;
    }

    PROCESSENTRY32W entry = {};
    entry.dwSize = sizeof(entry);

    if (Process32FirstW(snap, &entry))
    {
        do
        {
            ProcessInfo^ info = gcnew ProcessInfo();

            int pid = (int)entry.th32ProcessID;
            info->SetPID(pid);
            info->SetThreadCount((int)entry.cntThreads);
            info->SetName(pid == 0 ? "System Idle Process" : gcnew String(entry.szExeFile));

            bool fullAccess = false;
            HANDLE h = (HANDLE)OpenForQuery(pid, fullAccess);

            if (h != NULL)
            {
                info->SetFullPath(ReadPath(h));
                info->SetCpuTime(ReadCpuTime(h));
                info->SetPriorityClass(ReadPriority(h));
                ReadMemory(h, info);
                ReadOwner(h, info);

                if (fullAccess)
                {
                    info->SetVirtualSize(ReadVirtualSize(h));
                }
            }

            info->SetState(ReadState(pid, h));
            CalcCpuPercent(info, elapsedMs, newCpu);

            if (h != NULL)
            {
                CloseHandle(h);
            }

            result->Add(info);

        } while (Process32FirstW(snap, &entry));

        CloseHandle(snap);
        prevCpuTime = newCpu;
        return result;
    }
};

void* ProcessService::OpenForQuery(int pid, bool% fullAccess)
{
    HANDLE h = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, (DWORD)pid);

    if (h != NULL)
    {
        fullAccess = true;
        return h;
    }

    return OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, (DWORD)pid);
}

String^ ProcessService::ReadPath(void* h)
{
    wchar_t path[MAX_PATH * 2];
    DWORD size = MAX_PATH * 2;

    if (QueryFullProcessImageNameW((HANDLE)h, 0, path, &size))
    {
        return gcnew String(path);
    }

    return "";
}

TimeSpan ProcessService::ReadCpuTime(void* h)
{
    FILETIME created, exited, kernel, user;

    if (!GetProcessTimes((HANDLE)h, &created, &exited, &kernel, &user))
    {
        return TimeSpan::Zero;
    }

    ULARGE_INTEGER k, u;

    k.LowPart = kernel.dwLowDateTime;
    k.HighPart = kernel.dwHighDateTime;

    u.LowPart = user.dwLowDateTime;
    u.HighPart = user.dwHighDateTime;

    return TimeSpan((Int64)(k.QuadPart + u.QuadPart));
}

String^ ProcessService::ReadPriority(void* h)
{
    switch(GetPriorityClass((HANDLE)h))
    {
    case IDLE_PRIORITY_CLASS:         return "Idle";
    case BELOW_NORMAL_PRIORITY_CLASS: return "Below normal";
    case NORMAL_PRIORITY_CLASS:       return "Normal";
    case ABOVE_NORMAL_PRIORITY_CLASS: return "Above normal";
    case HIGH_PRIORITY_CLASS:         return "High";
    case REALTIME_PRIORITY_CLASS:     return "Realtime";
    default:                          return "";
    }
}

void ProcessService::ReadMemory(void* h, ProcessInfo^ info)
{
    PROCESS_MEMORY_COUNTERS_EX pmc = {};
    if (GetProcessMemoryInfo((HANDLE)h, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc)))
    {
        info->SetWorkingSet((Int64)pmc.WorkingSetSize);
        info->SetPrivateBytes((Int64)pmc.PrivateUsage);
    }
}

Int64 ProcessService::ReadVirtualSize(void* h)
{
    Int64 total = 0;
    MEMORY_BASIC_INFORMATION mbi;
    unsigned char* addr = nullptr;

    while (VirtualQueryEx((HANDLE)h,addr,&mbi, sizeof(mbi) == sizeof(mbi)))
    {
        if (mbi.State == MEM_COMMIT || mbi.State == MEM_RESERVE)
        {
            total += (Int64)mbi.RegionSize;
        }

        unsigned char* next = (unsigned char*)mbi.BaseAddress + mbi.RegionSize;

        if (next<= addr)
        {
            break;
        }

        addr = next;
    }

    return total;
}

void ProcessService::ReadOwner(void* h, ProcessInfo^ info)
{
    HANDLE hToken = NULL;

    if (!OpenProcessToken((HANDLE)h, TOKEN_QUERY, &hToken))
    {
        return;
    }

    DWORD size = 0;
    GetTokenInformation(hToken, TokenUser, NULL, 0, &size);
    std::vector<BYTE> buf(size);

    if (size > 0 && GetTokenInformation(hToken, TokenUser, buf.data(), size, &size))
    {
        PSID sid = ((TOKEN_USER*)buf.data())->User.Sid;

        wchar_t name[256], domain[256];
        DWORD nameLen = 256, domainLen = 256;
        SID_NAME_USE use;

        if (LookupAccountSidW(NULL, sid, name, &nameLen, domain, &domainLen, &use))
        {
            info->SetOwnerName(gcnew String(name));
        }

        LPWSTR sidText = NULL;

        if (ConvertSidToStringSidW(sid, &sidText))
        {
            info->SetOwnerSid(gcnew String(sidText));
            LocalFree(sidText);
        }
    }

    CloseHandle(hToken);
}

ProcessState ProcessService::ReadState(int pid, void* h)
{
    if (h == NULL)
    {
        return ProcessState::Unknown;
    }

    DWORD code;

    if (GetExitCodeProcess((HANDLE)h, &code) && code != STILL_ACTIVE)
    {
        return ProcessState::Terminated;
    }

    if (suspendedProcesses->Contains(pid))
    {
        return ProcessState::SuspendedByManager;
    }

    if (partiallySuspended->Contains(pid))
    {
        return ProcessState::PartiallySuspended;
    }

    return ProcessState::Active;
}

void ProcessService::CalcCpuPercent(ProcessInfo^ info, double elapsedMs, Dictionary<int, TimeSpan>^ newCpu)
{
    int pid = info->GetPID();

    TimeSpan oldCpu;

    if (elapsedMs >0 && prevCpuTime->TryGetValue(pid, oldCpu))
    {
        double usedMs = (info->GetCpuTime() - oldCpu).TotalMilliseconds;
        double percent = usedMs / (elapsedMs * Environment::ProcessorCount) * 100.0;

        info->SetCpuPercent(Math::Min(100.0, Math::Max(0.0, percent)));
    }
    else
    {
        info->SetCpuPercent(0);
    }

    newCpu[pid] = info->GetCpuTime();

}