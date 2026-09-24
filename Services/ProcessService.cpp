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