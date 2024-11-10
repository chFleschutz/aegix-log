//
// Example usage of the aegix-log library
// Basic logging
//

#include <aegix-log/log.h>
#include <aegix-log/sinks/console_sink.h>

#include <filesystem>
#include <iomanip>
#include <string>

int main()
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
	ALOG_INFO << "The answer is " << answer << " and pi is " << 3.14159 << "!";
	ALOG_INFO << str << " and " << std::filesystem::path("im/a/path");
	ALOG_INFO << std::setw(10) << std::setfill('0') << 42 << " is the answer";
	ALOG_INFO << "pi is " << std::setprecision(1) << 3.14159 << " i guess";

	// Severity threshold
	Aegix::Log::instance().setSeverityThreshold(Aegix::Log::Severity::Warn);
	ALOG_FATAL << "This is a critical message";
	ALOG_WARN << "This is a warning message";
	ALOG_INFO << "This is an info message";	 // Excluded
	ALOG_DEBUG << "This is a debug message"; // Excluded

	return 0;
}