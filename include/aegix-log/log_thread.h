#pragma once

#include "aegix-log/helper/singleton.h"
#include "aegix-log/helper/thread_safe_queue.h"
#include "aegix-log/log_entry.h"

#include <atomic>
#include <functional>
#include <thread>

namespace Aegix::Log
{
	class LogThread : public Singleton<LogThread>
	{
	public:
		LogThread(const LogThread&) = delete;
		LogThread(LogThread&&) = delete;

		~LogThread()
		{
			m_running = false;
			m_taskQueue.enqueue({ LogEntry(Severity::Trace), [](const LogEntry&) {} }); // Wake up the thread
			if (m_workerThread.joinable())
				m_workerThread.join();
		}

		LogThread& operator=(const LogThread&) = delete;
		LogThread& operator=(LogThread&&) = delete;

		void addTask(LogEntry&& entry, std::function<void(const LogEntry&)> sinkFunc)
		{
			if (m_running)
			{
				m_taskQueue.enqueue({ std::move(entry), sinkFunc });
			}
		}

	private:
		struct Task
		{
			LogEntry entry;
			std::function<void(const LogEntry&)> sinkFunc;
		};

		LogThread() : Singleton<LogThread>()
		{
			m_workerThread = std::thread(&LogThread::processTasks, this);
		}

		void processTasks()
		{
			while (m_running)
			{
				auto [entry, sink] = m_taskQueue.dequeue();
				sink(entry);
			}
		}

		ThreadSafeQueue<Task> m_taskQueue;

		std::thread m_workerThread;
		std::atomic<bool> m_running = true;

		friend void startLogThread();
	};
} // namespace Aegix::Log