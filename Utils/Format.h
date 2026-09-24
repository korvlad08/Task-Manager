#pragma once

#include "../Models/ProcessInfo.h"

using namespace System;

public ref class Format abstract sealed
{
public:
	static String^ Kb(Int64 bytes);
	static String^ Time(TimeSpan t);
	static String^ State(ProcessState state);
};