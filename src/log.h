#pragma once

#include "log_entry.h"
#include "logger.h"

#include <iostream>


// Logging macros

#define LOG(severity) Aegix::Logger::instance() += Aegix::LogEntry(severity)

#define LOG_CRITICAL LOG(Aegix::Severity::Critical)
#define LOG_WARNING	 LOG(Aegix::Severity::Warning)
#define LOG_INFO	 LOG(Aegix::Severity::Info)
#define LOG_DEBUG	 LOG(Aegix::Severity::Debug)
#define LOG_TRACE	 LOG(Aegix::Severity::Trace)

#ifdef NDEBUG
#undef LOG_DEBUG
#undef LOG_TRACE
#define LOG_DEBUG \
	if (false)    \
	LOG(Aegix::Severity::Debug)
#define LOG_TRACE \
	if (false)    \
	LOG(Aegix::Severity::Trace)
#endif


// Logging initialization

namespace Aegix::Log
{
Logger& init(Severity maxSeverity = Severity::Debug)
{
	static Logger logger(maxSeverity);
	return logger;
}
} // namespace Aegix::Log
