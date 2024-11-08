#pragma once

#include "aegix-log/log_entry.h"

namespace Aegix
{
	class LogSink
	{
	public:
		LogSink() = default;
		LogSink(const LogSink&) = delete;
		LogSink(LogSink&&) = delete;
		virtual ~LogSink() = default;

		LogSink& operator=(const LogSink&) = delete;
		LogSink& operator=(LogSink&&) = delete;

		virtual void log(const LogEntry& entry) = 0;
	};
} // namespace Aegix