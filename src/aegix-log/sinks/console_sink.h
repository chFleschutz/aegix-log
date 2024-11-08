#pragma once

#include "aegix-log/log_sink.h"

#include <iostream>

namespace Aegix
{
	class ConsoleSink : public LogSink
	{
	public:
		void log(const LogEntry& entry) override
		{
			auto localTime = std::chrono::current_zone()->to_local(entry.time());
			auto ms = localTime.time_since_epoch() % std::chrono::seconds(60);
			float seconds = std::chrono::duration<float>(ms).count();

			std::cout << std::format("{:%Y-%m-%d %H:%M:}{:0>6.3f}", localTime, seconds) << " " // Time
					  << std::left << std::setw(8) << toString(entry.severity()) << " " // Severity
					  << entry.message() << "\n";										// Message
		}
	};
} // namespace Aegix