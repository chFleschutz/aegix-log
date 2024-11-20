#pragma once

#include "aegix-log/log_entry.h"

#include <string>

namespace Aegix::Log
{
	inline auto toString(Severity severity) -> std::string_view
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