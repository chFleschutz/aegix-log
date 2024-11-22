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

auto main() -> int
{
	Aegix::Log::init(Aegix::Log::Trace) // Show all log messages
		.addSink<Aegix::Log::ConsoleSink>();

	ALOG::fatal("This is a critical message");
	ALOG::warn("This is a warning message");
	ALOG::info("This is an info message");
	ALOG::debug("This is a debug message"); // Will be stripped from release builds
	ALOG::trace("This is a trace message"); // Will be stripped from release builds

	return 0;
}