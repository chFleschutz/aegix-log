#pragma once

#include "aegix-log/log_entry.h"
#include "aegix-log/logger.h"

#define _ALOG_DISABLE_LINE_ \
	if (true)              \
	{                      \
		;                  \
	}                      \
	else

#ifdef AEGIX_LOG_DISABLE_ALL
#define _ALOG_IF_ALL_ _ALOG_DISABLE_LINE_
#else
#define _ALOG_IF_ALL_
#endif

#ifdef AEGIX_LOG_DISABLE_CRITICAL
#define _ALOG_IF_CRITICAL_ _ALOG_DISABLE_LINE_
#else
#define _ALOG_IF_CRITICAL_
#endif

#ifdef AEGIX_LOG_DISABLE_WARNING
#define _ALOG_IF_WARNING_ _ALOG_DISABLE_LINE_
#else
#define _ALOG_IF_WARNING_
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
#define _ALOG_(id, severity) Aegix::Log::instance<id>() += Aegix::LogEntry(severity).ref()

#define ALOG_(id, severity) _ALOG_IF_ALL_ _ALOG_(id, severity)
#define ALOG_CRITICAL_(id)	_ALOG_IF_CRITICAL_ ALOG_(id, Aegix::Severity::Fatal)
#define ALOG_WARNING_(id)	_ALOG_IF_WARNING_ ALOG_(id, Aegix::Severity::Warning)
#define ALOG_INFO_(id)		_ALOG_IF_INFO_ ALOG_(id, Aegix::Severity::Info)
#define ALOG_DEBUG_(id)		_ALOG_IF_DEBUG_ ALOG_(id, Aegix::Severity::Debug)
#define ALOG_TRACE_(id)		_ALOG_IF_TRACE_ ALOG_(id, Aegix::Severity::Trace)

#define ALOG(severity) ALOG_(Aegix::Log::DEFAULT_ID, severity)
#define ALOG_CRITICAL  ALOG_CRITICAL_(Aegix::Log::DEFAULT_ID)
#define ALOG_WARNING   ALOG_WARNING_(Aegix::Log::DEFAULT_ID)
#define ALOG_INFO	   ALOG_INFO_(Aegix::Log::DEFAULT_ID)
#define ALOG_DEBUG	   ALOG_DEBUG_(Aegix::Log::DEFAULT_ID)
#define ALOG_TRACE	   ALOG_TRACE_(Aegix::Log::DEFAULT_ID)

#define LOG(severity) ALOG(severity)
#define LOG_CRITICAL  ALOG_CRITICAL
#define LOG_WARNING	  ALOG_WARNING
#define LOG_INFO	  ALOG_INFO
#define LOG_DEBUG	  ALOG_DEBUG
#define LOG_TRACE	  ALOG_TRACE


namespace Aegix::Log
{
	constexpr int DEFAULT_ID = 0;

	template <int id = DEFAULT_ID>
	inline Logger<id>& init(Severity maxSeverity = Severity::Debug)
	{
		static Logger<id> logger(maxSeverity);
		return logger;
	}

	template <int id = DEFAULT_ID>
	inline Logger<id>& instance()
	{
		return Logger<id>::instance();
	}
} // namespace Aegix::Log
