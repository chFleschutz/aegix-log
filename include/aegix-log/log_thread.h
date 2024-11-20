#pragma once

#include "aegix-log/helper/token.h"
#include "aegix-log/log_entry.h"

#include <atomic>
#include <condition_variable>
#include <functional>
#include <queue>
#include <thread>

namespace Aegix::Log
{
	class LogThread
	{
	public:
		struct Task
		{
			LogEntry entry;
			std::function<void(const LogEntry&)> sinkFunc;
			Token& token;
		};

		LogThread() { m_workerThread = std::thread(&LogThread::processTasks, this); }
		LogThread(const LogThread&) = delete;
		LogThread(LogThread&&) = delete;
		~LogThread()
		{
			m_running = false;
			m_taskAvailable.notify_all();
			if (m_workerThread.joinable())
				m_workerThread.join();
		}

		auto operator=(const LogThread&) -> LogThread& = delete;
		auto operator=(LogThread&&) -> LogThread& = delete;

		void operator+=(Task&& task)
		{
			if (!m_running)
				return;

			task.token.increment();
			{
				std::lock_guard lock(m_queueMutex);
				m_taskQueue.push(std::move(task));
			}
			m_taskAvailable.notify_one();
		}

	private:
		void processTasks()
		{
			while (m_running)
			{
				std::unique_lock lock(m_queueMutex);
				m_taskAvailable.wait(lock, [this] { return !m_taskQueue.empty() || !m_running; });

				if (!m_running && m_taskQueue.empty())
					break;

				Task task = std::move(m_taskQueue.front());
				m_taskQueue.pop();
				lock.unlock();

				task.sinkFunc(task.entry);
				task.token.decrement();
			}
		}

		std::queue<Task> m_taskQueue;
		std::condition_variable m_taskAvailable;
		std::mutex m_queueMutex;

		std::thread m_workerThread;
		std::atomic<bool> m_running = true;
	};


	template <int ThreadID>
	inline auto initLogThread() -> std::shared_ptr<LogThread>
	{
		static std::shared_ptr<LogThread> logThread = std::make_shared<LogThread>();
		return logThread;
	}
} // namespace Aegix::Log