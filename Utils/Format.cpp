#include "Format.h"

using namespace System::Globalization;

String^ Format::Kb(Int64 bytes)
{
	Int64 kb = bytes / 1024;
	
	return kb.ToString("N0", CultureInfo::InvariantCulture) + "k";
}

String^ Format::Time(TimeSpan t)
{
	int hours = (int)t.TotalHours;

	return String::Format("{0:00}:{1:00}:{2:00}", hours, t.Minutes, t.Seconds);
}

String^ Format::State(ProcessState state)
{
	switch (state)
	{
	case ProcessState::Active:
	{
		return "Active";
	}
	case ProcessState::SuspendedByManager:
	{
		return "suspended";
	}
	case ProcessState::PartiallySuspended:
	{
		return "Partially suspended";
	}
	case ProcessState::Terminated:
	{
		return "Terminated";
	}
	default:
	{
		return "Unknown";
	}
	}
}