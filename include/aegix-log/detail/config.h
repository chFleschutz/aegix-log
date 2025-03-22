#pragma once

// Macros for configuring the logging system

namespace Aegix::Log::Detail
{
	// Enable/Disable logging for each severity level

#ifdef AEGIX_LOG_DISABLE_LOGGING
	constexpr bool LOGGING_ENABLED = false;
#else
	constexpr bool LOGGING_ENABLED = true;
#endif // AEGIX_LOG_DISABLE_LOGGING

#ifdef AEGIX_LOG_DISABLE_FATAL
	constexpr bool FATAL_ENABLED = false;
#else
	constexpr bool FATAL_ENABLED = true;
#endif // AEGIX_LOG_DISABLE_FATAL

#ifdef AEGIX_LOG_DISABLE_WARN
	constexpr bool WARN_ENABLED = false;
#else
	constexpr bool WARN_ENABLED = true;
#endif // AEGIX_LOG_DISABLE_WARN

#ifdef AEGIX_LOG_DISABLE_INFO
	constexpr bool INFO_ENABLED = false;
#else
	constexpr bool INFO_ENABLED = true;
#endif // AEGIX_LOG_DISABLE_INFO

#ifdef AEGIX_LOG_DISABLE_DEBUG
	constexpr bool DEBUG_ENABLED = false;
#else
	constexpr bool DEBUG_ENABLED = true;
#endif // AEGIX_LOG_DISABLE_DEBUG

#ifdef AEGIX_LOG_DISABLE_TRACE
	constexpr bool TRACE_ENABLED = false;
#else
	constexpr bool TRACE_ENABLED = true;
#endif // AEGIX_LOG_DISABLE_TRACE


	// Log fatal messages immediately (no async logging)

#ifdef AEGIX_LOG_FATAL_NO_ASYNC
	constexpr bool FATAL_ALLOW_ASYNC = false;
#else
	constexpr bool FATAL_ALLOW_ASYNC = true;
#endif // AEGIX_LOG_LOG_FATAL_IMMEDIATE
}
