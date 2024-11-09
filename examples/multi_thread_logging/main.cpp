//
// Example usage of the aegix-log library
// Multi-threaded logging
//

#include <aegix-log/log.h>
#include <aegix-log/sinks/console_sink.h>

#include <thread>
#include <vector>

int main()
{
	Aegix::Log::init() //
		.addSink<Aegix::ConsoleSink>();

	constexpr int numThreads = 5;
	constexpr int numMessages = 20;

	auto threadFun = [](int id)
	{
		for (int i = 0; i < numMessages; ++i)
		{
			ALOG_INFO << "Thread " << id << " message " << i;
		}
	};

	ALOG_INFO << "Starting " << numThreads << " threads, each logging " << numMessages << " messages";

	std::vector<std::thread> threads;
	threads.reserve(numThreads);
	for (int i = 0; i < numThreads; i++)
	{
		threads.emplace_back(threadFun, i);
	}

	ALOG_INFO << "All threads started";

	for (auto& thread : threads)
	{
		thread.join();
	}

	ALOG_INFO << "All threads finished";

	return 0;
}