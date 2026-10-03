#pragma once

#include "../Models/ProcessInfo.h"

using namespace System;

public ref class ThreadInfo
{
private:
	int tid;
	int ownerPid;
	double cpuPercent;
	String^ relativePriority;
	ProcessState state;

	int basePriority;
	TimeSpan cpuTime;
	int group;
	UInt64 affinityMask;

public:
	ThreadInfo()
	{
		tid = 0;
		ownerPid = 0;
		cpuPercent = 0;
		relativePriority = "";
		state = ProcessState::Unknown;

		basePriority = 0;
		cpuTime = TimeSpan::Zero;
		group = 0;
		affinityMask = 0;
	}

	//Get
	int GetTid()
	{
		return tid;
	}
	int GetOwnerPID() 
	{
		return ownerPid;
	}
	double GetCpuPercent() 
	{
		return cpuPercent;
	}
	String^ GetRelativePriority() 
	{ 
		return relativePriority;
	}
	ProcessState GetState() 
	{
		return state;
	}
	int GetBasePriority() 
	{
		return basePriority;
	}
	TimeSpan GetCpuTime() 
	{
		return cpuTime;
	}
	int GetGroup() 
	{
		return group; 
	}
	UInt64 GetAffinityMask() 
	{
		return affinityMask;
	}

	//Set
	void SetTID(int value) 
	{
		tid = value;
	}
	void SetOwnerPID(int value) 
	{
		ownerPid = value; 
	}
	void SetCpuPercent(double value) 
	{
		cpuPercent = value;
	}
	void SetRelativePriority(String^ value) 
	{
		relativePriority = value;
	}
	void SetState(ProcessState value) 
	{
		state = value;
	}
	void SetBasePriority(int value) 
	{
		basePriority = value; 
	}
	void SetCpuTime(TimeSpan value) 
	{
		cpuTime = value;
	}
	void SetGroup(int value) 
	{
		group = value;
	}
	void SetAffinityMask(UInt64 value) 
	{
		affinityMask = value; 
	}
};