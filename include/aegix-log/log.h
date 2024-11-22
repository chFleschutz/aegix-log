#pragma once

#include "aegix-log/log_entry.h"
#include "aegix-log/log_stream.h"
#include "aegix-log/logger.h"

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
