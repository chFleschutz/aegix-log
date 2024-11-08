#include "logger.h"

#include <cassert>

namespace Aegix
{
Logger::Logger(Severity severityThreshold) : m_severityThreshold{ severityThreshold }
{
	assert(!s_instance && "Logger already initialized");
	s_instance = this;
}

Logger::~Logger()
{
	assert(s_instance);
	s_instance = nullptr;
}

void Logger::operator+=(LogEntry& entry)
{
	if (entry.severity() > m_severityThreshold)
		return;

	for (const auto& sink : m_sinks)
	{
		sink->log(entry);
	}
}

Logger& Logger::instance()
{
	assert(s_instance && "Logger not initialized");
	return *s_instance;
}
} // namespace Aegix