# Aegix-Log

Simple and fast header-only C++20 logging library with no dependencies.

![aegix-log-console](https://github.com/user-attachments/assets/667fea57-cf1a-4dbd-a289-bf36af990a4e)

## Features

- Header-only
- Stream-style logging
- Format-string-style logging
- Thread-safe
- Asynchronous logging for improved performance
- Runtime log filtering
- Easily exclude specific log levels from builds
- Log to multiple destinations
- Support for multiple loggers
- Custom sink support for logging to custom destinations
- Custom formatter support

## Getting Started

The library requires a C++20 compiler. 

Since it's header-only, simply copy the [include](include/) folder to your project.

Alternatively you can add the library using cmake to automatically set the include paths:

1. Clone the repo to your desired location

```bash
git clone https://github.com/chFleschutz/aegix-log.git
```

2. Add the subdirectory of the library in your projects `CMakeLists.txt` file and link it to your target

```cmake
add_subdirectory(aegix-log)
target_link_libraries(MyProject PRIVATE Aegix::Log)
```

## Usage Examples

See the [examples](examples/) folder for full example projects.

**Basic usage**

```cpp
#include <aegix-log/log.h>
#include <aegix-log/sinks/console_sink.h>

int main()
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

	// Format string style logging
	ALOG::fatal("This is a fatal message");
	ALOG::warn("This is a warn message");
	ALOG::info("This is a info message");
	ALOG::debug("This is a debug message");
	ALOG::trace("This is a trace message");

	// Formatted logging
	ALOG::info() << "The answer is " << 42;
	ALOG::info("The answer is indeed {}", 42);
}
```

**Adding more Sinks**
```cpp
#include <aegix-log/log.h>
#include <aegix-log/sinks/console_sink.h>
#include <aegix-log/sinks/file_sink.h>

int main()
{
	Aegix::Log::init(Aegix::Severity::Trace) // Show all logs 
		.addSink<Aegix::ConsoleSink>()
		.addSink<Aegix::FileSink>("log.txt");

	// Printed in both the console and the log file
	ALOG::info("Hello World");
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
	Default = Aegix::Log::DEFAULT_LOGGER,
	Secondary
};

auto main() -> int
{
	// Default logger
	Aegix::Log::init(Aegix::Log::Trace) // Show all logs
		.addSink<Aegix::Log::ConsoleSink>();

	// Secondary logger
	Aegix::Log::init<Secondary>(Aegix::Log::Severity::Fatal) // Show only fatal logs
		.addSink<Aegix::Log::ConsoleSink>()
		.addSink<Aegix::Log::FileSink>("log.txt");

	// Print to default logger
	ALOG::fatal() << "This is a fatal message";
	ALOG::info<Default>() << "This is an info message";
	ALOG::debug<Default>() << "This is a debug message";

	// Print to secondary logger
	ALOG::fatal<Secondary>() << "Fatal message to secondary log";
	ALOG::warn<Secondary>() << "Warn message to secondary log"; // Excluded
}
```

**Exclude logs from release build**
```cpp
// Disable trace and debug messages in release mode
#ifdef NDEBUG
#define AEGIX_LOG_DISABLE_DEBUG
#define AEGIX_LOG_DISABLE_TRACE
#endif

#include <aegix-log/log.h>
#include <aegix-log/sinks/console_sink.h>

auto main() -> int
{
	Aegix::Log::init(Aegix::Log::Trace) 
		.addSink<Aegix::Log::ConsoleSink>();

	ALOG::fatal("This is a critical message");
	ALOG::warn("This is a warning message");
	ALOG::info("This is an info message");
	ALOG::debug("This is a debug message"); // Will be stripped from release builds
	ALOG::trace("This is a trace message"); // Will be stripped from release builds
}
```

**Custom log threads**
```cpp
#include <aegix-log/log.h>
#include <aegix-log/sinks/console_sink.h>

auto main() -> int
{
	// Logger 0 uses the current thread for logging
	Aegix::Log::init<0, Aegix::Log::NO_THREAD>(Aegix::Log::Trace)
		.addSink<Aegix::Log::ConsoleSink>();

	// Logger 1 uses a separate thread with ID 1
	Aegix::Log::init<1, 1>(Aegix::Log::Trace) 
		.addSink<Aegix::Log::ConsoleSink>();

	// Logger 2 uses a separate thread with ID 1 (same thread as Logger 1)
	Aegix::Log::init<2, 1>(Aegix::Log::Trace)
		.addSink<Aegix::Log::ConsoleSink>();
}
```
