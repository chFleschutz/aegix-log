//
// Example usage of the aegix-log library
// Custom log threads
//

#include <aegix-log/log.h>
#include <aegix-log/sinks/console_sink.h>

auto main() -> int
{
	// Logger 0 uses the current thread for logging
	Aegix::Log::init<0, Aegix::Log::NO_THREAD>(Aegix::Log::Trace) //
		.addSink<Aegix::Log::ConsoleSink>();

	// Logger 1 uses a separate thread with ID 1
	Aegix::Log::init<1, 1>(Aegix::Log::Trace) //
		.addSink<Aegix::Log::ConsoleSink>();

	// Logger 2 uses a separate thread with ID 1 (same thread as Logger 1)
	Aegix::Log::init<2, 1>(Aegix::Log::Trace) //
		.addSink<Aegix::Log::ConsoleSink>();
}