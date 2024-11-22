//
// Example usage of the aegix-log library
// Basic logging
//

#include <aegix-log/log.h>
#include <aegix-log/sinks/console_sink.h>

#include <filesystem>
#include <iomanip>
#include <numbers>
#include <string>

auto main() -> int
{
	// Initialize default logger
	Aegix::Log::init(Aegix::Log::Trace) // Show all log messages
		.addSink<Aegix::Log::ConsoleSink>();

	// Stream style logging
	ALOG::fatal() << "This is a fatal message";
	ALOG::warn() << "This is a warn message";
	ALOG::info() << "This is an info message";
	ALOG::debug() << "This is a debug message";
	ALOG::trace() << "This is a trace message";
	ALOG::info();

	// Format string style logging
	ALOG::fatal("This is a fatal message");
	ALOG::warn("This is a warn message");
	ALOG::info("This is a info message");
	ALOG::debug("This is a debug message");
	ALOG::trace("This is a trace message");
	ALOG::info("");

	// Formatted logging
	ALOG::info("This message is number: {}", 42);
	ALOG::info("This is {}, {} and {}", std::numbers::pi, 42, std::string("a string"));
	ALOG::info() << "This number is " << 42;
	ALOG::info() << "This is " << std::numbers::pi << ", " << 42 << " and " << std::string("a string");

	// Severity threshold
	ALOG::instance().setSeverityThreshold(ALOG::Warn);

	ALOG::fatal("This is a visible fatal message");
	ALOG::warn("This is a visible warn message");
	ALOG::info("This is info message will be excluded");   // Excluded
	ALOG::debug("This is debug message will be excluded"); // Excluded

	return 0;
}