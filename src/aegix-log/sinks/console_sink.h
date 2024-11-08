#pragma once

#include "aegix-log/format.h"
#include "aegix-log/log_sink.h"

#include <iostream>

namespace Aegix
{
	class ConsoleSink : public LogSink
	{
	public:
		void log(const LogEntry& entry) override { std::cout << Log::formatText(entry) << "\n"; }
	};
} // namespace Aegix