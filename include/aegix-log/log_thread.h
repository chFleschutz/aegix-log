#pragma once

#include "aegix-log/log_entry.h"

#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
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
			std::promise<void> promise;
		};

		LogThread() = default;
		LogThread(const LogThread&) = delete;
		LogThread(LogThread&&) = delete;
		~LogThread()
		{
			m_workerThread.request_stop();
			m_taskAvailable.notify_all();
		}

		auto operator=(const LogThread&) -> LogThread& = delete;
		auto operator=(LogThread&&) -> LogThread& = delete;

		auto addTask(LogEntry entry, std::function<void(const LogEntry&)> sinkFunc) -> std::future<void>
		{
			Task task{};
			task.entry = std::move(entry);
			task.sinkFunc = std::move(sinkFunc);
			auto future = task.promise.get_future();
			{
				std::lock_guard lock(m_queueMutex);
				m_taskQueue.push(std::move(task));
			}
			m_taskAvailable.notify_one();
			return future;
		}

	private:
		void processTasks(std::stop_token token)
		{
			while (!token.stop_requested() || !m_taskQueue.empty())
			{
				std::unique_lock lock(m_queueMutex);
				m_taskAvailable.wait(lock,
					[this, &token] { return !m_taskQueue.empty() || token.stop_requested(); });

				if (!m_taskQueue.empty())
				{
					Task task = std::move(m_taskQueue.front());
					m_taskQueue.pop();
					lock.unlock();

					task.sinkFunc(task.entry);
				}
			}
		}

		std::queue<Task> m_taskQueue;
		std::mutex m_queueMutex;
		std::condition_variable m_taskAvailable;
		std::jthread m_workerThread{ std::bind_front(&LogThread::processTasks, this) };
	};


	template <int ThreadID>
	inline auto initLogThread() -> std::shared_ptr<LogThread>
	{
		static std::shared_ptr<LogThread> logThread = std::make_shared<LogThread>();
		return logThread;
	}
} // namespace Aegix::Log