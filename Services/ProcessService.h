#pragma once
#include "../Models/ProcessInfo.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Diagnostics;

public ref class ProcessService
{
private:
	Dictionary<int, Int64>^ prevWorkingSet;
	Dictionary<int, TimeSpan>^ prevCpuTime;
	DateTime lastUpdate;

	void FillBasic(Process^ proc, ProcessInfo^ info);
	void FillNative(ProcessInfo^ info);
	void FillDeltas(ProcessInfo^ info, double elapsedMs,
		Dictionary<int, Int64>^ newWorkSet,
		Dictionary<int, TimeSpan>^ newCpu);

	static String^ ReadUser(void* hProcess);
public:
	List<ProcessInfo^>^ GetProcesses();
	ProcessService();
};