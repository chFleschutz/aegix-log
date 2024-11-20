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

		auto operator=(const LogEntry&) -> LogEntry& = delete;
		auto operator=(LogEntry&&) -> LogEntry& = default;

		template <typename T>
		auto operator<<(const T& value) -> LogEntry&&
		{
			m_stream << value;
			return static_cast<LogEntry&&>(*this);
		}

		[[nodiscard]] auto severity() const -> Severity{ return m_severity; }
		[[nodiscard]] auto time() const -> std::chrono::system_clock::time_point { return m_time; }
		[[nodiscard]] auto message() const -> std::string { return m_stream.str(); }
		[[nodiscard]] auto threadId() const -> std::thread::id { return m_threadId; }

	private:
		std::ostringstream m_stream;

		Severity m_severity;
		std::chrono::system_clock::time_point m_time;
		std::thread::id m_threadId;
	};
} // namespace Aegix::Log