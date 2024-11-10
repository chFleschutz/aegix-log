# Aegix-Log

Simple and fast header-only C++20 logging library with no dependencies.

![aegix-log-console](https://github.com/user-attachments/assets/01104779-6d63-4e40-8967-43af0909aedf)

## Features

- Fast
- Header-only
- Stream-based logging
- Thread-safe
- Asynchronous logging for improved performance
- Runtime log filtering
- Easily exclude specific log levels from builds
- Log to multiple destinations
- Support for multiple loggers
- Custom sink support for logging to custom destinations 

## Getting Started

The library requires a C++20 compiler. 

Since it's header-only, simply copy the [include](include/) folder to your project.

Alternatively you can add the library using cmake:

1. Clone the repo
```bash
git clone https://github.com/chFleschutz/aegix-log.git
```
2. Add the subdirectory of the library in your projects `CMakeLists.txt` file and link it to automatically set the include paths
```cmake
add_subdirectory(aegix-log)
target_link_libraries(MyProject PRIVATE Aegix::Log)
```

## Examples

See the [examples](examples/) folder for full example projects.

**Basic usage**

```cpp
#include <aegix-log/log.h>
#include <aegix-log/sinks/console_sink.h>

int main()
{
	// Initialize default logger
	Aegix::Log::init(Aegix::Severity::Trace) // Shows all log messages
		.addSink<Aegix::ConsoleSink>();

	// Basic logging
	ALOG_FATAL << "This is a fatal message";
	ALOG_WARN << "This is a warning message";
	ALOG_INFO << "This is an info message";
	ALOG_DEBUG << "This is a debug message";
	ALOG_TRACE << "This is a trace message";

	ALOG(Aegix::Severity::Fatal) << "This is an explicit critical message";
	ALOG(Aegix::Severity::Info) << "This is an explicit info message";
}
```

**Adding more Sinks**
```cpp
#include <aegix-log/log.h>
#include <aegix-log/sinks/console_sink.h>
#include <aegix-log/sinks/file_sink.h>

int main()
{
	Aegix::Log::init<SecondaryLog>(Aegix::Severity::Info) // 
		.addSink<Aegix::ConsoleSink>()
		.addSink<Aegix::FileSink>("log.txt");

	ALOG_INFO << "Log file: " << "log.txt";
}
```

**Creating multiple loggers**
```cpp
#include <aegix-log/log.h>
#include <aegix-log/sinks/console_sink.h>
#include <aegix-log/sinks/file_sink.h>

// Optional: create enum for IDs
enum LogID
{
	Log1 = Aegix::Log::DEFAULT_LOGGER,
	Log2
};

int main()
{
	// Default logger
	Aegix::Log::init(Aegix::Severity::Trace) // Show all log messages
		.addSink<Aegix::ConsoleSink>();

	// Secondary logger
	Aegix::Log::init<Log2>(Aegix::Severity::Fatal) //  Show only fatal messages
		.addSink<Aegix::FileSink>("log.txt");

	// Print to default logger
	ALOG_INFO << "Secondary log file: " << "log.txt";
	ALOG_FATAL << "This is a fatal message";
	ALOG_INFO_(Log1) << "This is an info message";  // Explicitly print to default logger

	// Print to secondary logger
	ALOG_FATAL_(Log2) << "Fatal message to secondary log";
	ALOG_INFO_(Log2) << "Info message to secondary log"; // Excluded
}
```

**Exclude logs from release build**
```cpp
// Exclude trace and debug messages in release mode
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

	ALOG_FATAL << "This is a critical message";
	ALOG_WARN << "This is a warning message";
	ALOG_INFO << "This is an info message";
	ALOG_DEBUG << "This is a debug message"; // Completely stripped from release builds
	ALOG_TRACE << "This is a trace message"; // Completely stripped from release builds

	return 0;
}
```
