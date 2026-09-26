#pragma once
#include "../Models/ProcessInfo.h"

using namespace System;
using namespace System::Collections::Generic;

public ref class ProcessService
{
public:
    ProcessService();
    List<ProcessInfo^>^ GetProcesses();

private:
    Dictionary<int, TimeSpan>^ prevCpuTime;
    DateTime lastUpdate;

    List<int>^ suspendedProcesses;
    List<int>^ partiallySuspended;

    static void* OpenForQuery(int pid, bool% fullAccess);
    static String^ ReadPath(void* h);
    static TimeSpan ReadCpuTime(void* h);
    static String^ ReadPriority(void* h);
    static void ReadMemory(void* h, ProcessInfo^ info);
    static Int64 ReadVirtualSize(void* h);
    static void ReadOwner(void* h, ProcessInfo^ info);

    ProcessState ReadState(int pid, void* h);
    void CalcCpuPercent(ProcessInfo^ info, double elapsedMs,
        Dictionary<int, TimeSpan>^ newCpu);
};