#pragma once

#include "aegix-log/log_entry.h"
#include "aegix-log/logger.h"

#define _ALOG_DISABLE_LINE_ \
	if (true)               \
	{                       \
		;                   \
	}                       \
	else

#ifdef AEGIX_LOG_DISABLE_ALL
#define _ALOG_IF_ALL_ _ALOG_DISABLE_LINE_
#else
#define _ALOG_IF_ALL_
#endif

#ifdef AEGIX_LOG_DISABLE_FATAL
#define _ALOG_IF_FATAL_ _ALOG_DISABLE_LINE_
#else
#define _ALOG_IF_FATAL_
#endif

#ifdef AEGIX_LOG_DISABLE_WARN
#define _ALOG_IF_WARN_ _ALOG_DISABLE_LINE_
#else
#define _ALOG_IF_WARN_
#endif

#ifdef AEGIX_LOG_DISABLE_INFO
#define _ALOG_IF_INFO_ _ALOG_DISABLE_LINE_
#else
#define _ALOG_IF_INFO_
#endif

#ifdef AEGIX_LOG_DISABLE_DEBUG
#define _ALOG_IF_DEBUG_ _ALOG_DISABLE_LINE_
#else
#define _ALOG_IF_DEBUG_
#endif

#ifdef AEGIX_LOG_DISABLE_TRACE
#define _ALOG_IF_TRACE_ _ALOG_DISABLE_LINE_
#else
#define _ALOG_IF_TRACE_
#endif


// Logging macros
#define _ALOG_(id, severity) Aegix::Log::instance<id>() += Aegix::LogEntry(severity)

#define ALOG_(id, severity) _ALOG_IF_ALL_ _ALOG_(id, severity)
#define ALOG_FATAL_(id)		_ALOG_IF_FATAL_ ALOG_(id, Aegix::Severity::Fatal)
#define ALOG_WARN_(id)		_ALOG_IF_WARN_ ALOG_(id, Aegix::Severity::Warn)
#define ALOG_INFO_(id)		_ALOG_IF_INFO_ ALOG_(id, Aegix::Severity::Info)
#define ALOG_DEBUG_(id)		_ALOG_IF_DEBUG_ ALOG_(id, Aegix::Severity::Debug)
#define ALOG_TRACE_(id)		_ALOG_IF_TRACE_ ALOG_(id, Aegix::Severity::Trace)

#define ALOG(severity) ALOG_(Aegix::Log::DEFAULT_ID, severity)
#define ALOG_FATAL	   ALOG_FATAL_(Aegix::Log::DEFAULT_ID)
#define ALOG_WARN	   ALOG_WARN_(Aegix::Log::DEFAULT_ID)
#define ALOG_INFO	   ALOG_INFO_(Aegix::Log::DEFAULT_ID)
#define ALOG_DEBUG	   ALOG_DEBUG_(Aegix::Log::DEFAULT_ID)
#define ALOG_TRACE	   ALOG_TRACE_(Aegix::Log::DEFAULT_ID)

#define LOG(severity) ALOG(severity)
#define LOG_FATAL	  ALOG_FATAL
#define LOG_WARN	  ALOG_WARN
#define LOG_INFO	  ALOG_INFO
#define LOG_DEBUG	  ALOG_DEBUG
#define LOG_TRACE	  ALOG_TRACE


namespace Aegix::Log
{
	constexpr int DEFAULT_ID = 0;

	inline void startLogThread()
	{
		static LogThread logThread;
	}

	template <int id = DEFAULT_ID>
	inline Logger<id>& init(Severity maxSeverity = Severity::Debug)
	{
		startLogThread();
		static Logger<id> logger(maxSeverity);
		return logger;
	}

	template <int id = DEFAULT_ID>
	inline Logger<id>& instance()
	{
		return Logger<id>::instance();
	}
} // namespace Aegix::Log
