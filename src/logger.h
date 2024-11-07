#pragma once

#include "log_entry.h"
#include "log_sink.h"

#include <iostream>
#include <memory>
#include <vector>

namespace Aegix
{
class Logger
{
public:
	explicit Logger(Severity maxSeverity);
	Logger(const Logger&) = delete;
	~Logger();

	Logger& operator=(const Logger&) = delete;

	void operator+=(LogEntry& entry);

	template <typename T, typename... Args>
	Logger& addSink(Args&&... args)
	{
		static_assert(std::is_base_of_v<LogSink, T>, "T must derive from LogSink");
		m_sinks.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
		return *this;
	}

	static Logger& instance();

private:
	inline static Logger* s_instance = nullptr;

	Severity m_maxSeverity;
	std::vector<std::unique_ptr<LogSink>> m_sinks;
};
} // namespace Aegix