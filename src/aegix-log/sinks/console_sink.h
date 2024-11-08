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
			std::cout << "[" << toString(entry.severity()) << "] " << entry.message() << std::endl;
		}
	};
} // namespace Aegix