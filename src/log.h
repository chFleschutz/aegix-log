#pragma once

#include <iostream>

#define LOG_CRITICAL(msg) Aegix::Logger::instance() << "[CRITICAL] " << msg << std::endl
#define LOG_WARNING(msg) Aegix::Logger::instance() << "[WARNING] " << msg << std::endl
#define LOG_INFO(msg) Aegix::Logger::instance() << "[INFO] " << msg << std::endl

#ifdef _DEBUG
#define LOG_DEBUG(msg) Aegix::Logger::instance() << "[DEBUG] " << msg << std::endl
#define LOG_TRACE(msg) Aegix::Logger::instance() << "[TRACE] " << msg << std::endl
#else
#define LOG_DEBUG(msg) ((void)0)
#define LOG_TRACE(msg) ((void)0)
#endif

namespace Aegix
{
class Logger
{
public:
	Logger(const Logger&) = delete;
	~Logger() = default;

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
		static Logger logger;
		return logger;
	}

private:
	Logger() = default;
};
} // namespace Aegix
