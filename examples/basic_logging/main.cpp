//
// Example usage of the aegix-log library
// Basic logging
//

#include <aegix-log/log.h>
#include <aegix-log/sinks/console_sink.h>

#include <filesystem>
#include <iomanip>
#include <string>
#include <numbers>

auto main() -> int
{
	// Initialize default logger
	Aegix::Log::init(Aegix::Log::Trace) // Show all log messages
		.addSink<Aegix::Log::ConsoleSink>();
	
	// Basic logging
	ALOG_FATAL << "This is a critical message";
	ALOG_WARN << "This is a warning message";
	ALOG_INFO << "This is an info message";
	ALOG_DEBUG << "This is a debug message";
	ALOG_TRACE << "This is a trace message";

	ALOG(Aegix::Log::Severity::Fatal) << "This is an explicit critical message";
	ALOG(Aegix::Log::Severity::Info) << "This is an explicit info message";

	// Formatted logging
	int answer = 42;
	std::string str = "Im a string";
	ALOG_INFO;
	ALOG_INFO << std::setw(20) << std::setfill('-') << " 20->";
	ALOG_INFO << "The answer is " << answer << " and pi is " << std::numbers::pi << "!";
	ALOG_INFO << str << " and " << std::filesystem::path("im/a/path");
	ALOG_INFO << std::setw(10) << std::setfill('0') << 42 << " is the answer";
	ALOG_INFO << "pi is " << std::setprecision(1) << std::numbers::pi << " i guess";

	// Severity threshold
	Aegix::Log::instance().setSeverityThreshold(Aegix::Log::Severity::Warn);
	ALOG_FATAL << "This is a critical message";
	ALOG_WARN << "This is a warning message";
	ALOG_INFO << "This is an info message";	 // Excluded
	ALOG_DEBUG << "This is a debug message"; // Excluded

	// Format string logging
	ALOG::instance().setSeverityThreshold(ALOG::Trace);

	Aegix::Log::log(Aegix::Log::Fatal, "Hello World");
	Aegix::Log::warn("Warn this World");
	Aegix::Log::info("Inform the World about {}", 42); 

	ALOG::warn("Warn this World again");
	ALOG::fatal("Hello World again");
	ALOG::log(ALOG::Info, "Inform the World again");

	ALOG::instance<ALOG::DEFAULT_LOGGER>().fatal("Fatal World again");

	// Stream style logging
	ALOG::log(ALOG::Info) << "Hello World";
	ALOG::warn() << "Warn this World";
	ALOG::fatal() << "Fatal World " << 42 << " times";

	ALOG::info<0>() << "Hello World";

	ALOG::fatal("This is the last fatal message for today");

	return 0;
}