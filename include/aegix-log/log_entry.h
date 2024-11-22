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

	struct LogEntry
	{
		Severity severity;
		std::chrono::system_clock::time_point time;
		std::thread::id threadId;
		std::string message;
	};

	// TODO: Move this to a separate file 
	class LogStream
	{
	public:
		LogStream(Severity severity)
			: m_entry{ severity, std::chrono::system_clock::now(), std::this_thread::get_id(), std::string() }
		{
		}

		LogStream(const LogStream&) = delete;
		LogStream(LogStream&&) = default;
		~LogStream() = default;

		auto operator=(const LogStream&) -> LogStream& = delete;
		auto operator=(LogStream&&) -> LogStream& = default;

		template <typename T>
		auto operator<<(const T& value) -> LogStream&
		{
			m_stream << value;
			return *this;
		}

		// TODO: this could cause issues after entry was moved
		[[nodiscard]] auto entry() const -> LogEntry
		{
			LogEntry entry = std::move(m_entry);
			entry.message = m_stream.str();
			return entry;
		}

	private:
		std::ostringstream m_stream;
		LogEntry m_entry;
	};
} // namespace Aegix::Log