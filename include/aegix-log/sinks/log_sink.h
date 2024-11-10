#pragma once

#include "aegix-log/formatter/formatter.h"
#include "aegix-log/log_entry.h"

namespace Aegix::Log
{
	class LogSink
	{
	public:
		LogSink(std::unique_ptr<Log::Formatter> formatter) : m_formatter(std::move(formatter)) {}
		LogSink(const LogSink&) = delete;
		LogSink(LogSink&&) = delete;
		virtual ~LogSink() = default;

		LogSink& operator=(const LogSink&) = delete;
		LogSink& operator=(LogSink&&) = delete;

		virtual void log(const LogEntry& entry) = 0;

		std::string format(const LogEntry& entry) const { return m_formatter->format(entry); }

	protected:
		std::unique_ptr<Log::Formatter> m_formatter;
	};
} // namespace Aegix