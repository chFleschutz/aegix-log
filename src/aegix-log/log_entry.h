#pragma once

#include <chrono>
#include <sstream>

namespace Aegix
{
	enum class Severity
	{
		Trace,
		Debug,
		Info,
		Warning,
		Fatal
	};

	class LogEntry
	{
	public:
		LogEntry(Severity severity)
			: m_severity{ severity }, m_time{ std::chrono::system_clock::now() }
		{
		}

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

		Severity severity() const { return m_severity; }
		std::chrono::system_clock::time_point time() const { return m_time; }
		std::string message() const { return m_stream.str(); }

		LogEntry& ref() { return *this; }

	private:
		std::ostringstream m_stream;

		Severity m_severity;
		std::chrono::system_clock::time_point m_time;
	};
} // namespace Aegix