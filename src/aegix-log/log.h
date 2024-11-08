#pragma once

#include "aegix-log/log_entry.h"
#include "aegix-log/logger.h"


// Logging macros
#define ALOG_INTERNAL(severity) Aegix::Logger::instance() += Aegix::LogEntry(severity).ref()

#define ALOG(severity) ALOG_INTERNAL(severity)
#define ALOG_CRITICAL  ALOG(Aegix::Severity::Critical)
#define ALOG_WARNING   ALOG(Aegix::Severity::Warning)
#define ALOG_INFO	   ALOG(Aegix::Severity::Info)
#define ALOG_DEBUG	   ALOG(Aegix::Severity::Debug)
#define ALOG_TRACE	   ALOG(Aegix::Severity::Trace)

#define LOG(severity) ALOG(severity)
#define LOG_CRITICAL  ALOG_CRITICAL
#define LOG_WARNING	  ALOG_WARNING
#define LOG_INFO	  ALOG_INFO
#define LOG_DEBUG	  ALOG_DEBUG
#define LOG_TRACE	  ALOG_TRACE


#define AEGIX_DISABLE_LINE \
	if (true)              \
	{                      \
		;                  \
	}                      \
	else

// Disable debug and trace logging in release builds
#ifdef NDEBUG
#undef LOG_DEBUG
#undef LOG_TRACE
#define LOG_DEBUG AEGIX_DISABLE_LINE LOG(Aegix::Severity::Debug)
#define LOG_TRACE AEGIX_DISABLE_LINE LOG(Aegix::Severity::Trace)
#undef ALOG_DEBUG
#undef ALOG_TRACE
#define ALOG_DEBUG AEGIX_DISABLE_LINE ALOG(Aegix::Severity::Debug)
#define ALOG_TRACE AEGIX_DISABLE_LINE ALOG(Aegix::Severity::Trace))
#endif

// Define AEGIX_NO_LOGGING to disable logging completely
#ifdef AEGIX_NO_LOGGING
#undef ALOG(severity)
#define ALOG(severity) AEGIX_DISABLE_LINE ALOG_INTERNAL(severity)
#endif


namespace Aegix::Log
{
Logger& init(Severity maxSeverity = Severity::Debug)
{
	static Logger logger(maxSeverity);
	return logger;
}
} // namespace Aegix::Log
