#pragma once

#include "aegix-log/format.h"
#include "aegix-log/log_sink.h"

#include <iostream>

namespace Aegix
{
	class ConsoleSink : public LogSink
	{
	public:
		void log(const LogEntry& entry) override
		{
			if (entry.severity() >= Severity::Warning)
			{
				std::cerr << Log::formatText(entry) << "\n";
			}
			else
			{
				std::cout << Log::formatText(entry) << "\n";
			}
		}
	};
} // namespace Aegix