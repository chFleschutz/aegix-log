// Example usage of the aegix-log library


// Disable trace and debug messages in release mode
#ifdef NDEBUG
#define AEGIX_DISABLE_LOG_TRACE
#define AEGIX_DISABLE_LOG_DEBUG
#endif

#include <aegix-log/log.h>
#include <aegix-log/sinks/console_sink.h>
#include <aegix-log/sinks/file_sink.h>

#include <filesystem>
#include <string>

int main()
{
	Aegix::Log::init(Aegix::Severity::Trace) // Show all log messages
		.addSink<Aegix::ConsoleSink>();

	// Basic logging
	ALOG_CRITICAL << "This is a critical message";
	ALOG_WARNING << "This is a warning message";
	ALOG_INFO << "This is an info message";
	ALOG_DEBUG << "This is a debug message";
	ALOG_TRACE << "This is a trace message";
	ALOG(Aegix::Severity::Critical) << "This is an explicit critical message";
	ALOG(Aegix::Severity::Warning) << "This is an explicit warning message";

	// Formatted logging
	ALOG_INFO;
	ALOG_INFO << std::setw(20) << std::setfill('-') << " 20->";
	ALOG_INFO << "The answer is " << 42 << " and pi is " << 3.14159 << "!";
	ALOG_INFO << std::string("Im a string") << " and " << std::filesystem::path("im/a/path");
	ALOG_INFO << std::setw(10) << std::setfill('0') << 42 << " is the answer";
	ALOG_INFO << std::setprecision(1) << 3.14159 << " is pi";

	// Severity threshold
	Aegix::Log::instance().setSeverityThreshold(Aegix::Severity::Warning);
	ALOG_CRITICAL << "This is a critical message";
	ALOG_WARNING << "This is a warning message";
	ALOG_INFO << "This is an info message";	 // Excluded
	ALOG_DEBUG << "This is a debug message"; // Excluded

	// Multiple loggers
	std::filesystem::path logFile = std::filesystem::current_path() / "logs" / "log.txt";
	Aegix::Log::init<1>(Aegix::Severity::Critical) // Only shows critical messages
		.addSink<Aegix::FileSink>(logFile);

	ALOG_INFO << "Log-file: " << logFile;						// Only shows in logger 0
	ALOG_CRITICAL_(1) << "This is a critical message to log 1"; // Only shows in logger 1
	ALOG_INFO_(1) << "This is an info message to log 1";		// Excluded by severity threshold

	return 0;
}