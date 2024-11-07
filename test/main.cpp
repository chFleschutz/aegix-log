#include "log.h"
#include "sinks/console_sink.h"
#include "sinks/file_sink.h"

#include <filesystem>
#include <string>

int main()
{
	Aegix::Log::init(Aegix::Severity::Trace) //
		.addSink<Aegix::ConsoleSink>()
		.addSink<Aegix::FileSink>("logs/log.txt");

	LOG_INFO << "Log-file: " << std::filesystem::current_path() / "logs" / "log.txt";

	LOG_CRITICAL << "This is a critical message";
	LOG_WARNING << "This is a warning message";
	LOG_INFO << "This is an info message";
	LOG_DEBUG << "This is a debug message"; // Excluded in release builds
	LOG_TRACE << "This is a trace message"; // Excluded in release builds

	LOG_INFO;
	LOG_INFO << std::setw(20) << std::setfill('-') << " 20->";
	LOG_INFO << "The answer is " << 42 << " and pi is " << 3.14159 << "!";
	LOG_INFO << std::string("Im a string") << " and " << std::filesystem::path("im/a/path");
	LOG_INFO << std::setw(10) << std::setfill('0') << 42 << " is the answer";
	LOG_INFO << std::setprecision(1) << 3.14159 << " is pi";

	Aegix::Logger::instance().setSeverityThreshold(Aegix::Severity::Warning);
	LOG_CRITICAL << "This is a critical message";
	LOG_WARNING << "This is a warning message";
	LOG_INFO << "This is an info message";	// Excluded
	LOG_DEBUG << "This is a debug message"; // Excluded

	return 0;
}