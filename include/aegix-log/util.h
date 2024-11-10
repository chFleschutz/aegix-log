#pragma once

#include "aegix-log/log_entry.h"

namespace Aegix::Log
{
	inline std::string_view toString(Severity severity)
	{
		switch (severity)
		{
		case Severity::Fatal: return "FATAL";
		case Severity::Warn: return "WARN";
		case Severity::Info: return "INFO";
		case Severity::Debug: return "DEBUG";
		case Severity::Trace: return "TRACE";
		default: return "UNKNOWN";
		}
	}
} // namespace Aegix::Log