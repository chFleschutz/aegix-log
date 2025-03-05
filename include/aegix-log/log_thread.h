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
	/// @brief A thread that processes log tasks
	class LogThread
	{
	public:
		static constexpr size_t MAX_QUEUE_SIZE = 1000;

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

		[[nodiscard]] auto queueSize() const -> size_t
		{
			std::lock_guard lock(m_queueMutex);
			return m_taskQueue.size();
		}

		/// @brief Adds a log task to the thread queue which will be processed by the worker thread
		/// @return If successful, returns a future that will be set when the task is completed otherwise 'std::nullopt'
		/// @note If successful, 'entry' will be moved into the queue and is no longer valid
		auto addTask(LogEntry& entry, std::function<void(const LogEntry&)> sinkFunc) -> std::optional<std::future<void>>
		{
			assert(sinkFunc && "Sink function must be valid");

			Task task{};
			auto future = task.promise.get_future();
			{
				std::lock_guard lock(m_queueMutex);
				if (m_taskQueue.size() >= MAX_QUEUE_SIZE)
					return std::nullopt;

				// Only move if queue can accept the task
				task.entry = std::move(entry);
				task.sinkFunc = std::move(sinkFunc);

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

		mutable std::mutex m_queueMutex;
		std::queue<Task> m_taskQueue;
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