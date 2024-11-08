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
			switch (entry.severity())
			{
			case Severity::Fatal: 
				std::cerr << "\033[41m" << Log::formatText(entry) << "\033[0m\n"; 
				break;
			case Severity::Warning: 
				std::cerr << "\033[33m" << Log::formatText(entry) << "\033[0m\n";
				break;
			default: 
				std::cout << Log::formatText(entry) << "\n";
				break;
			}
		}
	};
} // namespace Aegix