#pragma once

#include <chrono>
#include <sstream>
#include <thread>

namespace Aegix::Log
{
	enum class Severity
	{
		Trace,
		Debug,
		Info,
		Warn,
		Fatal
	};

	using enum Severity;

	class LogEntry
	{
	public:
		LogEntry(Severity severity)
			: m_severity{ severity }, m_time{ std::chrono::system_clock::now() },
			  m_threadId{ std::this_thread::get_id() }
		{
		}

		LogEntry(const LogEntry&) = delete;
		LogEntry(LogEntry&&) = default;
		~LogEntry() = default;

		LogEntry& operator=(const LogEntry&) = delete;
		LogEntry& operator=(LogEntry&&) = default;

		template <typename T>
		LogEntry&& operator<<(const T& value)
		{
			m_stream << value;
			return static_cast<LogEntry&&>(*this);
		}

		Severity severity() const { return m_severity; }
		std::chrono::system_clock::time_point time() const { return m_time; }
		std::string message() const { return m_stream.str(); }
		std::thread::id threadId() const { return m_threadId; }

		LogEntry& ref() { return *this; }

	private:
		std::ostringstream m_stream;

		Severity m_severity;
		std::chrono::system_clock::time_point m_time;
		std::thread::id m_threadId;
	};
} // namespace Aegix::Log