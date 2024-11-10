#pragma once

#include "aegix-log/sinks/log_sink.h"

#include <iostream>

namespace Aegix
{
	class ConsoleSink : public LogSink
	{
	public:
		ConsoleSink(std::unique_ptr<Log::Formatter> formatter) : LogSink(std::move(formatter)) {}

		void log(const LogEntry& entry) override
		{
			auto message = format(entry);
			switch (entry.severity())
			{
			case Severity::Fatal: std::cerr << "\033[41m" << message << "\033[0m\n"; break;
			case Severity::Warn: std::cerr << "\033[33m" << message << "\033[0m\n"; break;
			default: std::cout << message << "\n"; break;
			}
		}
	};
} // namespace Aegix