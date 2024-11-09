#pragma once

#include "aegix-log/helper/singleton.h"
#include "aegix-log/log_entry.h"

#include <atomic>
#include <condition_variable>
#include <functional>
#include <queue>
#include <thread>

namespace Aegix::Log
{
	class TaskToken
	{
	public:
		TaskToken() = default;
		TaskToken(const TaskToken&) = delete;
		TaskToken(TaskToken&&) = delete;
		~TaskToken() { waitPending(); }

		TaskToken& operator=(const TaskToken&) = delete;
		TaskToken& operator=(TaskToken&&) = delete;

		void waitPending()
		{
			std::unique_lock lock(m_mutex);
			m_condition.wait(lock, [this] { return m_pendingCount == 0; });
		}

		void taskQueued()
		{
			std::lock_guard lock(m_mutex);
			m_pendingCount++;
		}
		void taskFinished()
		{
			std::lock_guard lock(m_mutex);
			m_pendingCount--;
			if (m_pendingCount == 0)
				m_condition.notify_all();
		}

	private:
		uint32_t m_pendingCount = 0;
		std::condition_variable m_condition;
		std::mutex m_mutex;
	};


	class LogThread
	{
	public:
		LogThread() { m_workerThread = std::thread(&LogThread::processTasks, this); }
		LogThread(const LogThread&) = delete;
		LogThread(LogThread&&) = delete;
		~LogThread()
		{
			m_running = false;
			m_condition.notify_all();
			if (m_workerThread.joinable())
				m_workerThread.join();
		}

		LogThread& operator=(const LogThread&) = delete;
		LogThread& operator=(LogThread&&) = delete;

		void addTask(LogEntry&& entry, std::function<void(const LogEntry&)> sinkFunc, TaskToken& token)
		{
			if (!m_running)
				return;

			token.taskQueued();

			std::lock_guard lock(m_mutex);
			m_taskQueue.push({ std::move(entry), sinkFunc, token });
			m_condition.notify_one();
		}

	private:
		struct Task
		{
			LogEntry entry;
			std::function<void(const LogEntry&)> sinkFunc;
			TaskToken& token;
		};

		void processTasks()
		{
			while (m_running)
			{
				std::unique_lock lock(m_mutex);
				m_condition.wait(lock, [this] { return !m_taskQueue.empty() || !m_running; });
				if (!m_running)
					break;

				Task task = std::move(m_taskQueue.front());
				m_taskQueue.pop();
				lock.unlock();

				task.sinkFunc(task.entry);
				task.token.taskFinished();
			}
		}

		std::queue<Task> m_taskQueue;
		std::condition_variable m_condition;
		std::mutex m_mutex;

		std::thread m_workerThread;
		std::atomic<bool> m_running = true;
	};

	inline std::shared_ptr<LogThread> initLogThread()
	{
		static std::shared_ptr<LogThread> logThread = std::make_shared<LogThread>();
		return logThread;
	}
} // namespace Aegix::Log