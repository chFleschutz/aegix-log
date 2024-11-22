#pragma once

#include "aegix-log/log_entry.h"

#include <chrono>
#include <sstream>
#include <thread>

namespace Aegix::Log
{
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

		// TODO: Remove the copy of the entry
		[[nodiscard]] auto entry() const -> LogEntry
		{
			LogEntry entry = m_entry;
			entry.message = m_stream.str();
			return entry;
		}

	private:
		std::ostringstream m_stream;
		LogEntry m_entry;
	};
} // namespace Aegix::Log