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
	DefaultLog = Aegix::Log::DEFAULT_LOGGER,
	SecondaryLog
};

auto main() -> int
{
	// Default logger
	Aegix::Log::init(Aegix::Log::Trace) // Show all log messages
		.addSink<Aegix::Log::ConsoleSink>();

	// Secondary logger
	std::filesystem::path logFile = std::filesystem::current_path() / "log.txt";
	Aegix::Log::init<SecondaryLog>(Aegix::Log::Severity::Info) // 
		.addSink<Aegix::Log::ConsoleSink>()
		.addSink<Aegix::Log::FileSink>(logFile);

	// Print to default logger
	ALOG::info() << "Secondary log file: " << logFile;
	ALOG::fatal() << "This is a fatal message";
	ALOG::info<DefaultLog>() << "This is an info message";
	ALOG::debug<DefaultLog>() << "This is a debug message";

	// Print to secondary logger
	ALOG::fatal<SecondaryLog>() << "Fatal message to secondary log";
	ALOG::warn<SecondaryLog>() << "Warn message to secondary log";
	ALOG::info<SecondaryLog>() << "Info message to secondary log";

	return 0;
}