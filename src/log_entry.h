#pragma once

#include <sstream>

namespace Aegix
{

enum class Severity
{
	Critical,
	Warning,
	Info,
	Debug,
	Trace
};

static std::string_view toString(Severity severity)
{
	switch (severity)
	{
	case Severity::Critical: return "CRITICAL";
	case Severity::Warning: return "WARNING";
	case Severity::Info: return "INFO";
	case Severity::Debug: return "DEBUG";
	case Severity::Trace: return "TRACE";
	default: return "UNKNOWN";
	}
}

class LogEntry
{
public:
	LogEntry(Severity severity) : m_severity{ severity } {}
	LogEntry(const LogEntry&) = delete;
	LogEntry(LogEntry&&) = delete;
	~LogEntry() = default;

	LogEntry& operator=(const LogEntry&) = delete;
	LogEntry& operator=(LogEntry&&) = delete;

	template <typename T>
	LogEntry& operator<<(const T& value)
	{
		m_stream << value;
		return *this;
	}

	LogEntry& ref() { return *this; }

private:
	Severity m_severity;
	std::ostringstream m_stream;

	friend class Logger;
};

} // namespace Aegix