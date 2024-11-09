//
// Example usage of the aegix-log library
// Conditional logging
//

// Disable trace and debug messages in release mode
#ifdef NDEBUG
#define AEGIX_LOG_DISABLE_DEBUG
#define AEGIX_LOG_DISABLE_TRACE
#endif

#include <aegix-log/log.h>
#include <aegix-log/sinks/console_sink.h>

int main()
{
	Aegix::Log::init(Aegix::Severity::Trace) // Show all log messages
		.addSink<Aegix::ConsoleSink>();

	ALOG_CRITICAL << "This is a critical message";
	ALOG_WARNING << "This is a warning message";
	ALOG_INFO << "This is an info message";
	ALOG_DEBUG << "This is a debug message"; // Completely stripped from release builds
	ALOG_TRACE << "This is a trace message"; // Completely stripped from release builds

	return 0;
}