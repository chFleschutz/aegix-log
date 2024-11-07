#pragma once

#include <cassert>
#include <iostream>
#include <sstream>

#define LOG(severity) Aegix::Logger::instance() += Aegix::LogEntry(severity)

#define LOG_CRITICAL LOG(Aegix::Severity::Critical)
#define LOG_WARNING	 LOG(Aegix::Severity::Warning)
#define LOG_INFO	 LOG(Aegix::Severity::Info)

#ifdef _DEBUG
#define LOG_DEBUG LOG(Aegix::Severity::Debug)
#define LOG_TRACE LOG(Aegix::Severity::Trace)
#else
#define LOG_DEBUG \
	if (false)    \
	LOG(Aegix::Severity::Debug)
#define LOG_TRACE \
	if (false)    \
	LOG(Aegix::Severity::Trace)
#endif

namespace Aegix
{

class Logger;

namespace Log
{
Logger& init();
} // namespace Log

enum class Severity
{
	Critical,
	Warning,
	Info,
	Debug,
	Trace
};

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

private:
	Severity m_severity;
	std::ostringstream m_stream;

	friend class Logger;
};


class Logger
{
public:
	Logger(const Logger&) = delete;
	~Logger()
	{
		assert(s_instance);
		s_instance = nullptr;
	}

	Logger& operator=(const Logger&) = delete;

	void operator+=(LogEntry& entry) { print(entry.m_severity, entry.m_stream.str()); }
	void operator+=(LogEntry&& entry) { print(entry.m_severity, entry.m_stream.str()); }

	static Logger& instance()
	{
		assert(s_instance && "Logger not initialized");
		return *s_instance;
	}

private:
	Logger()
	{
		assert(!s_instance && "Logger already initialized");
		s_instance = this;
	}

	std::string_view severityToString(Severity severity)
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

	void print(Severity severity, const std::string& message)
	{
		std::cout << "[" << severityToString(severity) << "] " << message << std::endl;
	}

	inline static Logger* s_instance = nullptr;

	friend Logger& Log::init();
};
} // namespace Aegix
