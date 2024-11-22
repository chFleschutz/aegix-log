//
// Example usage of the aegix-log library
// Multi-threaded logging
//

#include <aegix-log/log.h>
#include <aegix-log/sinks/console_sink.h>

#include <thread>
#include <vector>

auto main() -> int
{
	Aegix::Log::init() //
		.addSink<Aegix::Log::ConsoleSink>();

	constexpr int numThreads = 5;
	constexpr int numMessages = 20;

	auto threadFun = [](int id)
	{
		for (int i = 0; i < numMessages; ++i)
		{
			ALOG::info("Thread {} message {}", id, i);
		}
	};

	ALOG::info("Starting {} threads, each logging {} messages", numThreads, numMessages);

	std::vector<std::thread> threads;
	threads.reserve(numThreads);
	for (int i = 0; i < numThreads; i++)
	{
		threads.emplace_back(threadFun, i);
	}

	ALOG::info("All threads started");

	for (auto& thread : threads)
	{
		thread.join();
	}

	ALOG::info("All threads finished");

	return 0;
}