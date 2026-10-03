#pragma once

#include "ThreadInfo.h"

using namespace System;
using namespace System::Collections::Generic;

public ref class ThreadService
{
private:
	Dictionary<int, TimeSpan>^ prevCpuTime;
	DateTime lastUpdate;

	List<int>^ suspendedThreads;

	static TimeSpan ReadCpuTime(void* h);
	static String^ ReadRelativePriority(void* h);
	static void ReadAffinity(void* h, ThreadInfo^ info);

	ProcessState ReadState(int tid, void* h);
	void CalcCpuPercent(ThreadInfo^ info, double elapsedMs, Dictionary<int, TimeSpan>^newCpu);

public:
	ThreadService();
	List<ThreadInfo^>^ GetThreads(int pid);
};