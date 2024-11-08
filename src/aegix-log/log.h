#pragma once

#include "aegix-log/log_entry.h"
#include "aegix-log/logger.h"

#define AEGIX_DISABLE_LINE \
	if (true)              \
	{                      \
		;                  \
	}                      \
	else

#ifdef AEGIX_DISABLE_LOG_ALL
#define ALOG_IF_ALL AEGIX_DISABLE_LINE
#else
#define ALOG_IF_ALL
#endif

#ifdef AEGIX_DISABLE_LOG_CRITICAL
#define ALOG_IF_CRITICAL AEGIX_DISABLE_LINE
#else
#define ALOG_IF_CRITICAL
#endif

#ifdef AEGIX_DISABLE_LOG_WARNING
#define ALOG_IF_WARNING AEGIX_DISABLE_LINE
#else
#define ALOG_IF_WARNING
#endif

#ifdef AEGIX_DISABLE_LOG_INFO
#define ALOG_IF_INFO AEGIX_DISABLE_LINE
#else
#define ALOG_IF_INFO
#endif

#ifdef AEGIX_DISABLE_LOG_DEBUG
#define ALOG_IF_DEBUG AEGIX_DISABLE_LINE
#else
#define ALOG_IF_DEBUG
#endif

#ifdef AEGIX_DISABLE_LOG_TRACE
#define ALOG_IF_TRACE AEGIX_DISABLE_LINE
#else
#define ALOG_IF_TRACE
#endif


// Logging macros
#define ALOG_INTERNAL(id, severity) Aegix::Log::instance<id>() += Aegix::LogEntry(severity).ref()

#define ALOG_(id, severity) ALOG_IF_ALL ALOG_INTERNAL(id, severity)
#define ALOG_CRITICAL_(id)	ALOG_IF_CRITICAL ALOG_(id, Aegix::Severity::Critical)
#define ALOG_WARNING_(id)	ALOG_IF_WARNING ALOG_(id, Aegix::Severity::Warning)
#define ALOG_INFO_(id)		ALOG_IF_INFO ALOG_(id, Aegix::Severity::Info)
#define ALOG_DEBUG_(id)		ALOG_IF_DEBUG ALOG_(id, Aegix::Severity::Debug)
#define ALOG_TRACE_(id)		ALOG_IF_TRACE ALOG_(id, Aegix::Severity::Trace)

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
