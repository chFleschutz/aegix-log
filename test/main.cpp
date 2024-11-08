#include <aegix-log/log.h>
#include <aegix-log/sinks/console_sink.h>
#include <aegix-log/sinks/file_sink.h>

#include <filesystem>
#include <string>

int main()
{
	Aegix::Log::init(Aegix::Severity::Trace) // Show all log messages
		.addSink<Aegix::ConsoleSink>()
		.addSink<Aegix::FileSink>("logs/log.txt");

	ALOG_INFO << "Log-file: " << std::filesystem::current_path() / "logs" / "log.txt";
	
	ALOG_CRITICAL << "This is a critical message";
	ALOG_WARNING << "This is a warning message";
	ALOG_INFO << "This is an info message";
	ALOG_DEBUG << "This is a debug message"; // Excluded in release builds
	ALOG_TRACE << "This is a trace message"; // Excluded in release builds

	ALOG_INFO;
	ALOG_INFO << std::setw(20) << std::setfill('-') << " 20->";
	ALOG_INFO << "The answer is " << 42 << " and pi is " << 3.14159 << "!";
	ALOG_INFO << std::string("Im a string") << " and " << std::filesystem::path("im/a/path");
	ALOG_INFO << std::setw(10) << std::setfill('0') << 42 << " is the answer";
	ALOG_INFO << std::setprecision(1) << 3.14159 << " is pi";

	Aegix::Logger::instance().setSeverityThreshold(Aegix::Severity::Warning);
	ALOG_CRITICAL << "This is a critical message";
	ALOG_WARNING << "This is a warning message";
	ALOG_INFO << "This is an info message"; // Excluded
	ALOG_DEBUG << "This is a debug message"; // Excluded

	return 0;
}