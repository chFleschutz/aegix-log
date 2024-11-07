#pragma once

#include "log_entry.h"

#include <iostream>

namespace Aegix
{
class Logger
{
public:
	explicit Logger(Severity maxSeverity);
	Logger(const Logger&) = delete;
	~Logger();

	Logger& operator=(const Logger&) = delete;

	void operator+=(LogEntry& entry)
	{
		if (entry.m_severity > m_maxSeverity)
			return;

		std::cout << "[" << toString(entry.m_severity) << "] " << entry.m_stream.str() << std::endl;
	}

	static Logger& instance();

private:
	inline static Logger* s_instance = nullptr;

	Severity m_maxSeverity;
};
} // namespace Aegix