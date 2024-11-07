#pragma once

#include "log_entry.h"

#include <iostream>

namespace Aegix
{
class Logger
{
public:
	Logger();
	Logger(const Logger&) = delete;
	~Logger();

	Logger& operator=(const Logger&) = delete;

	void operator+=(LogEntry& entry) { print(entry.m_severity, entry.m_stream.str()); }
	void operator+=(LogEntry&& entry) { print(entry.m_severity, entry.m_stream.str()); }

	static Logger& instance();

private:
	void print(Severity severity, const std::string& message)
	{
		std::cout << "[" << toString(severity) << "] " << message << std::endl;
	}

	inline static Logger* s_instance = nullptr;
};
} // namespace Aegix