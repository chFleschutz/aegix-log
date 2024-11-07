#pragma once

#include "log_entry.h"

namespace Aegix
{
class LogSink
{
public:
	LogSink() = default;
	virtual ~LogSink() = default;

	virtual void log(const LogEntry& entry) = 0;
};

} // namespace Aegix