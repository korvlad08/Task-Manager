#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <windows.h>
#include <tlhelp32.h>

#include "ThreadService.h"

ThreadService::ThreadService()
{
	prevCpuTime = gcnew Dictionary<int, TimeSpan>();
	suspendedThreads = gcnew List<int>();
	lastUpdate = DateTime::Now;
}

List<ThreadInfo^>^ ThreadService::GetThreads(int pid)
{
	List<ThreadInfo^>^ result = gcnew List<ThreadInfo^>();
	Dictionary<int, TimeSpan>^ newCpu = gcnew Dictionary<int, TimeSpan>();

	DateTime now = DateTime::Now;
	double elapsedMs = (now-lastUpdate).TotalMilliseconds;
	lastUpdate = now;

	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (snap == INVALID_HANDLE_VALUE)
	{
		return result;
	}

	THREADENTRY32 te = {};
	te.dwSize = sizeof(te);

    if (Thread32First(snap, &te))
    {
        do
        {
            if ((int)te.th32OwnerProcessID != pid)
            {
                continue;
            }

            ThreadInfo^ info = gcnew ThreadInfo();
            int tid = (int)te.th32ThreadID;

            info->SetTID(tid);
            info->SetOwnerPID(pid);
            info->SetBasePriority((int)te.tpBasePri);

            HANDLE h = OpenThread(THREAD_QUERY_LIMITED_INFORMATION, FALSE, te.th32ThreadID);
            if (h != NULL)
            {
                info->SetCpuTime(ReadCpuTime(h));
                info->SetRelativePriority(ReadRelativePriority(h));
                ReadAffinity(h, info);
            }

            info->SetState(ReadState(tid, h));
            CalcCpuPercent(info, elapsedMs, newCpu);

            if (h != NULL)
                CloseHandle(h);

            result->Add(info);

        } while (Thread32Next(snap, &te));
    }

    CloseHandle(snap);
    prevCpuTime = newCpu;
    return result;
}

TimeSpan ThreadService::ReadCpuTime(void* h)
{
    FILETIME created, exited, kernel, user;

    if (!GetThreadTimes((HANDLE)h, &created, &exited, &kernel, &user))
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

String^ ThreadService::ReadRelativePriority(void* h)
{
    int p = GetThreadPriority((HANDLE)h);

    switch (p)
    {
    case THREAD_PRIORITY_IDLE:
    {
        return "Idle";
    }
    case THREAD_PRIORITY_LOWEST:
    {
        return "Lowest";
    }
    case THREAD_PRIORITY_BELOW_NORMAL:
    {
        return "Below normal"; 
    }
    case THREAD_PRIORITY_NORMAL:
    {
        return "Normal"; 
    }
    case THREAD_PRIORITY_ABOVE_NORMAL: 
    {
        return "Above normal";
    }
    case THREAD_PRIORITY_HIGHEST: 
    {
        return "Highest";
    }
    case THREAD_PRIORITY_TIME_CRITICAL: 
    {
        return "Time critical"; 
    }
    case THREAD_PRIORITY_ERROR_RETURN: 
    {
        return ""; 
    }
    default: 
    {
        return p.ToString();
    }
    }
}

void ThreadService::ReadAffinity(void* h, ThreadInfo^ info)
{
    GROUP_AFFINITY ga = {};
    if (GetThreadGroupAffinity((HANDLE)h, &ga))
    {
        info->SetGroup((int)ga.Group);
        info->SetAffinityMask((UInt64)ga.Mask);
    }
}

ProcessState ThreadService::ReadState(int tid, void* h)
{
    if (h == NULL)
    {
        return ProcessState::Unknown;
    }

    DWORD code;
    if (GetExitCodeThread((HANDLE)h, &code) && code != STILL_ACTIVE)
    {
        return ProcessState::Terminated;
    }

    if (suspendedThreads->Contains(tid))
    {
        return ProcessState::SuspendedByManager;
    }

    return ProcessState::Active;
}

void ThreadService::CalcCpuPercent(ThreadInfo^ info, double elapsedMs, Dictionary<int, TimeSpan>^ newCpu)
{
    int tid = info->GetTid();
    TimeSpan oldCpu;

    if (elapsedMs > 0 && prevCpuTime->TryGetValue(tid, oldCpu))
    {
        double usedMs = info->GetCpuTime().TotalMilliseconds - oldCpu.TotalMilliseconds;
        double percent = usedMs / (elapsedMs * Environment::ProcessorCount) * 100.0;
        info->SetCpuPercent(Math::Min(100.0, Math::Max(0.0, percent)));
    }
    else
        info->SetCpuPercent(0);

    newCpu[tid] = info->GetCpuTime();
}