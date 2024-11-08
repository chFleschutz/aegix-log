#pragma once

#include "aegix-log/log_entry.h"

namespace Aegix::Log
{
	inline std::string_view toString(Severity severity)
	{
		switch (severity)
		{
		case Severity::Critical: return "CRITICAL";
		case Severity::Warning: return "WARNING";
		case Severity::Info: return "INFO";
		case Severity::Debug: return "DEBUG";
		case Severity::Trace: return "TRACE";
		default: return "UNKNOWN";
		}
	}

	inline std::string formatText(const LogEntry& entry)
	{
		auto localTime = std::chrono::current_zone()->to_local(entry.time());
		auto ms = localTime.time_since_epoch() % std::chrono::seconds(60);
		float seconds = std::chrono::duration<float>(ms).count();

		return std::format("{:%Y-%m-%d %H:%M:}{:0>6.3f} | {:<8} | {}",
			localTime,
			seconds,
			toString(entry.severity()),
			entry.message());
	}
} // namespace Aegix::Log