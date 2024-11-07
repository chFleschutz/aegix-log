#pragma once

#include <cassert>
#include <iostream>
#include <sstream>

#define LOG_(severity) Aegix::Logger::instance() += Aegix::LogEntry() << "[" #severity "] "

#define LOG_CRITICAL LOG_(CRITICAL)
#define LOG_WARNING	 LOG_(WARNING)
#define LOG_INFO	 LOG_(INFO)

#ifdef _DEBUG
#define LOG_DEBUG LOG_(DEBUG)
#define LOG_TRACE LOG_(TRACE)
#else
#define LOG_DEBUG \
	if (false)    \
	LOG(DEBUG)
#define LOG_TRACE \
	if (false)    \
	LOG(TRACE)
#endif

namespace Aegix
{

class Logger;

namespace Log
{
Logger& init();
}


class LogEntry
{
public:
	LogEntry() = default;
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

	void operator+=(LogEntry& entry) { std::cout << entry.m_stream.str() << std::endl; }

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

	inline static Logger* s_instance = nullptr;

	friend Logger& Log::init();
};
} // namespace Aegix
