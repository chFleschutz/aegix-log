#pragma once

#include <chrono>
#include <string>
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

	inline constexpr auto toString(Severity severity) -> std::string_view
	{
		switch (severity)
		{
		case Severity::Fatal: return "FATAL";
		case Severity::Warn: return "WARN";
		case Severity::Info: return "INFO";
		case Severity::Debug: return "DEBUG";
		case Severity::Trace: return "TRACE";
		default: return "UNKNOWN";
		}
	}

	struct LogEntry
	{
		Severity severity;
		std::chrono::system_clock::time_point time;
		std::thread::id threadId;
		std::string message;
	};
} // namespace Aegix::Log