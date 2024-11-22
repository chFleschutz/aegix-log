#pragma once

#include "aegix-log/log_entry.h"
#include "aegix-log/logger.h"

#include <chrono>
#include <sstream>
#include <thread>

namespace Aegix::Log
{
	template <int LoggerID>
	class LogStream
	{
	public:
		explicit LogStream(Severity severity)
			: m_entry{ severity, std::chrono::system_clock::now(), std::this_thread::get_id(), std::string() }
		{
		}

		~LogStream()
		{
			m_entry.message = m_stream.str();
			Logger<LoggerID>::instance().log(std::move(m_entry));
		}

		LogStream(const LogStream&) = delete;
		LogStream(LogStream&&) = default;

		auto operator=(const LogStream&) -> LogStream& = delete;
		auto operator=(LogStream&&) -> LogStream& = default;

		template <typename T>
		auto operator<<(const T& value) -> LogStream&
		{
			m_stream << value;
			return *this;
		}

		template <typename T>
		auto operator<<(const T* pointer) -> LogStream&
		{
			m_stream << pointer;
			return *this;
		}

	private:
		std::ostringstream m_stream;
		LogEntry m_entry;
	};

	class NoOpLogStream
	{
	public:
		template <typename T>
		auto constexpr operator<<(const T&) -> NoOpLogStream&
		{
			return *this;
		}
	};
} // namespace Aegix::Log