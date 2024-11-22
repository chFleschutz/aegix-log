#pragma once

#include "aegix-log/log_entry.h"
#include "aegix-log/log_stream.h"
#include "aegix-log/logger.h"

#define ALOG_DISABLE_LINE \
	if (true)             \
	{                     \
		;                 \
	}                     \
	else

#ifdef AEGIX_LOG_DISABLE_LOGGING
#define ALOG_IF_ALL ALOG_DISABLE_LINE
#else
#define ALOG_IF_ALL
#endif

#ifdef AEGIX_LOG_DISABLE_FATAL
#define ALOG_IF_FATAL ALOG_DISABLE_LINE
#else
#define ALOG_IF_FATAL
#endif

#ifdef AEGIX_LOG_DISABLE_WARN
#define ALOG_IF_WARN ALOG_DISABLE_LINE
#else
#define ALOG_IF_WARN
#endif

#ifdef AEGIX_LOG_DISABLE_INFO
#define ALOG_IF_INFO ALOG_DISABLE_LINE
#else
#define ALOG_IF_INFO
#endif

#ifdef AEGIX_LOG_DISABLE_DEBUG
#define ALOG_IF_DEBUG ALOG_DISABLE_LINE
#else
#define ALOG_IF_DEBUG
#endif

#ifdef AEGIX_LOG_DISABLE_TRACE
#define ALOG_IF_TRACE ALOG_DISABLE_LINE
#else
#define ALOG_IF_TRACE
#endif

// Logging macros
#define ALOG_(id, severity) ALOG_IF_ALL Aegix::Log::log<id>(severity)
#define ALOG_FATAL_(id)		ALOG_IF_FATAL ALOG_(id, Aegix::Log::Severity::Fatal)
#define ALOG_WARN_(id)		ALOG_IF_WARN ALOG_(id, Aegix::Log::Severity::Warn)
#define ALOG_INFO_(id)		ALOG_IF_INFO ALOG_(id, Aegix::Log::Severity::Info)
#define ALOG_DEBUG_(id)		ALOG_IF_DEBUG ALOG_(id, Aegix::Log::Severity::Debug)
#define ALOG_TRACE_(id)		ALOG_IF_TRACE ALOG_(id, Aegix::Log::Severity::Trace)

#define ALOG(severity) ALOG_(Aegix::Log::DEFAULT_LOGGER, severity)
#define ALOG_FATAL	   ALOG_FATAL_(Aegix::Log::DEFAULT_LOGGER)
#define ALOG_WARN	   ALOG_WARN_(Aegix::Log::DEFAULT_LOGGER)
#define ALOG_INFO	   ALOG_INFO_(Aegix::Log::DEFAULT_LOGGER)
#define ALOG_DEBUG	   ALOG_DEBUG_(Aegix::Log::DEFAULT_LOGGER)
#define ALOG_TRACE	   ALOG_TRACE_(Aegix::Log::DEFAULT_LOGGER)

namespace ALOG = Aegix::Log;

namespace Aegix::Log
{
	constexpr int DEFAULT_LOGGER = 0;
	constexpr int DEFAULT_THREAD = 0;
	constexpr int NO_THREAD = -1;

	template <int LogID = DEFAULT_LOGGER, int ThreadID = DEFAULT_THREAD>
	inline auto init(Severity severityThreshold = Severity::Debug) -> Logger<LogID>&
	{
		if constexpr (ThreadID == NO_THREAD)
			return initLogger<LogID>(nullptr, severityThreshold);

		auto logThread = initLogThread<ThreadID>();
		return initLogger<LogID>(logThread, severityThreshold);
	}

	template <int LogID = DEFAULT_LOGGER>
	inline auto instance() -> Logger<LogID>&
	{
		return Logger<LogID>::instance();
	}

	/// @brief This function bypasses the macro disabling for specific severity levels
	template <typename... Args>
	inline void log(Severity severity, std::format_string<Args...> fmt, Args&&... args)
	{
		instance().log(severity, fmt, std::forward<Args>(args)...);
	}

	template <typename... Args>
	inline void fatal(std::format_string<Args...> fmt, Args&&... args)
	{
		instance().fatal(fmt, std::forward<Args>(args)...);
	}

	template <typename... Args>
	inline void warn(std::format_string<Args...> fmt, Args&&... args)
	{
		instance().warn(fmt, std::forward<Args>(args)...);
	}

	template <typename... Args>
	inline void info(std::format_string<Args...> fmt, Args&&... args)
	{
		instance().info(fmt, std::forward<Args>(args)...);
	}

	template <typename... Args>
	inline void debug(std::format_string<Args...> fmt, Args&&... args)
	{
		instance().debug(fmt, std::forward<Args>(args)...);
	}

	template <typename... Args>
	inline void trace(std::format_string<Args...> fmt, Args&&... args)
	{
		instance().trace(fmt, std::forward<Args>(args)...);
	}

	/// @brief This function bypasses the macro disabling for specific severity levels
	template <int LogID = DEFAULT_LOGGER>
	inline constexpr auto log(Severity severity)
	{
#ifdef AEGIX_LOG_DISABLE_LOGGING
		return NoOpLogStream();
#else
		return LogStream<LogID>(severity);
#endif
	}

	template <int LogID = DEFAULT_LOGGER>
	inline constexpr auto fatal()
	{
#ifdef AEGIX_LOG_DISABLE_FATAL
		return NoOpLogStream();
#else
		return log<LogID>(Severity::Fatal);
#endif 
	}

	template <int LogID = DEFAULT_LOGGER>
	inline constexpr auto warn()
	{
#ifdef AEGIX_LOG_DISABLE_WARN
		return NoOpLogStream();
#else
		return log<LogID>(Severity::Warn);
#endif
	}

	template <int LogID = DEFAULT_LOGGER>
	inline constexpr auto info()
	{
#ifdef AEGIX_LOG_DISABLE_INFO
		return NoOpLogStream();
#else
		return log<LogID>(Severity::Info);
#endif
	}

	template <int LogID = DEFAULT_LOGGER>
	inline constexpr auto debug()
	{
#ifdef AEGIX_LOG_DISABLE_DEBUG
		return NoOpLogStream();
#else
		return log<LogID>(Severity::Debug);
#endif
	}

	template <int LogID = DEFAULT_LOGGER>
	inline constexpr auto trace()
	{
#ifdef AEGIX_LOG_DISABLE_TRACE
		return NoOpLogStream();
#else
		return log<LogID>(Severity::Trace);
#endif
	}
} // namespace Aegix::Log
