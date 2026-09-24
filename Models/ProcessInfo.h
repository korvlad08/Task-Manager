#pragma once

using namespace System;

public enum class ProcessState
{
	Active,
	SuspendedByManager,
	PartiallySuspended,
	Terminated,
	Unknown
};

public ref class ProcessInfo
{
private:
	int pid;
	String^ name;
	String^ fullPath;

	TimeSpan cpuTime;
	double cpuPercent;

	String^ priorityClass;

	ProcessState state;

	Int64 workingSet;
	Int64 virtualSize;
	Int64 privateBytes;

	int threadCount;
	String^ ownerName;
	String^ ownerSid;

public:
	//Constructor
	ProcessInfo()
{
	pid = 0;
	name = "";
	fullPath = "";
	cpuTime = TimeSpan::Zero;
	cpuPercent = 0;
	priorityClass = "";
	state = ProcessState::Unknown;
	workingSet = 0;
	virtualSize = 0;
	privateBytes = 0;
	threadCount = 0;
	ownerName = "";
	ownerSid = "";
}

	//Get
	int GetPID() 
	{
		return pid; 
	}
	String^ GetName()
	{
		return name; 
	}
	String^ GetFullPath() 
	{ 
		return fullPath;
	}

	TimeSpan GetCpuTime() 
	{ 
		return cpuTime;
	}
	double GetCpuPercent() 
	{ 
		return cpuPercent;
	}

	String^ GetPriorityClass() 
	{
		return priorityClass;
	}

	ProcessState GetState() 
	{ 
		return state; 
	}

	Int64 GetWorkingSet()
	{ 
		return workingSet;
	}
	Int64 GetVirtualSize() 
	{ 
		return virtualSize; 
	}
	Int64 GetPrivateBytes() 
	{ 
		return privateBytes; 
	}

	int GetThreadCount()
	{ 
		return threadCount;
	}
	String^ GetOwnerName()
	{
		return ownerName;
	}
	String^ GetOwnerSid() 
	{
		return ownerSid; 
	}

	//Set
	void SetPID(int value) 
	{
		pid = value;
	}
	void SetName(String^ value) 
	{ 
		name = value;
	}
	void SetFullPath(String^ value) 
	{
		fullPath = value; 
	}

	void SetCpuTime(TimeSpan value) 
	{
		cpuTime = value;
	}
	void SetCpuPercent(double value) 
	{
		cpuPercent = value;
	}

	void SetPriorityClass(String^ value) 
	{ 
		priorityClass = value;
	}

	void SetState(ProcessState value) 
	{
		state = value; 
	}

	void SetWorkingSet(Int64 value) 
	{
		workingSet = value;
	}
	void SetVirtualSize(Int64 value) 
	{
		virtualSize = value;
	}
	void SetPrivateBytes(Int64 value) 
	{ 
		privateBytes = value; 
	}

	void SetThreadCount(int value) 
	{
		threadCount = value; 
	}
	void SetOwnerName(String^ value) 
	{
		ownerName = value; 
	}
	void SetOwnerSid(String^ value) 
	{
		ownerSid = value; 
	}
};