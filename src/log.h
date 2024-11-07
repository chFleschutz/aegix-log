#pragma once

#include <cassert>
#include <iostream>

#define LOG_(severity) Aegix::Logger::instance() << "[" #severity "] "

#define LOG_CRITICAL LOG_(CRITICAL)
#define LOG_WARNING LOG_(WARNING)
#define LOG_INFO LOG_(INFO)

#ifdef _DEBUG
#define LOG_DEBUG LOG_(DEBUG)
#define LOG_TRACE LOG_(TRACE)
#else
#define LOG_DEBUG \
	if (false)    \
	ALOG(DEBUG)
#define LOG_TRACE \
	if (false)    \
	ALOG(TRACE)
#endif

namespace Aegix
{
class Logger
{
public:
	Logger()
	{
		assert(!s_instance && "Logger already initialized");
		s_instance = this;
	}

	Logger(const Logger&) = delete;
	~Logger()
	{
		assert(s_instance);
		s_instance = nullptr;
	}

	Logger& operator=(const Logger&) = delete;

	template <typename T>
	Logger& operator<<(const T& value)
	{
		std::cout << value;
		return *this;
	}

	Logger& operator<<(std::ostream& (*func)(std::ostream&))
	{
		func(std::cout);
		return *this;
	}

	static Logger& instance()
	{
		assert(s_instance && "Logger not initialized");
		return *s_instance;
	}

private:
	inline static Logger* s_instance = nullptr;
};
} // namespace Aegix

namespace Aegix::Log
{
Logger& init()
{
	static Logger logger;
	return logger;
}
}; // namespace Aegix::Log