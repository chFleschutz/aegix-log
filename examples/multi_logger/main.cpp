//
// Example usage of the aegix-log library
// Multiple loggers
//

#include <aegix-log/log.h>
#include <aegix-log/sinks/console_sink.h>
#include <aegix-log/sinks/file_sink.h>

// Define custom log IDs
enum LogID
{
	DefaultLog = Aegix::Log::DEFAULT_ID,
	SecondaryLog
};

int main()
{
	// Default logger
	Aegix::Log::init(Aegix::Severity::Trace) // Show all log messages
		.addSink<Aegix::ConsoleSink>();

	// Secondary logger
	std::filesystem::path logFile = std::filesystem::current_path() / "log.txt";
	Aegix::Log::init<SecondaryLog>(Aegix::Severity::Info) // 
		.addSink<Aegix::ConsoleSink>()
		.addSink<Aegix::FileSink>(logFile);

	// Print to default logger
	ALOG_INFO << "Secondary log file: " << logFile;
	ALOG_FATAL << "This is a fatal message";
	ALOG_INFO_(DefaultLog) << "This is an info message";
	ALOG_(DefaultLog, Aegix::Severity::Debug) << "This is a debug message";

	// Print to secondary logger
	ALOG_FATAL_(SecondaryLog) << "Fatal message to secondary log";
	ALOG_INFO_(SecondaryLog) << "Info message to secondary log";
	ALOG_DEBUG_(SecondaryLog) << "Debug message to secondary log";

	return 0;
}