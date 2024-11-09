#pragma once

#include "aegix-log/helper/singleton.h"
#include "aegix-log/helper/thread_safe_queue.h"
#include "aegix-log/log_entry.h"

#include <atomic>
#include <functional>
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


	class LogThread : public Singleton<LogThread>
	{
	public:
		LogThread(const LogThread&) = delete;
		LogThread(LogThread&&) = delete;

		~LogThread()
		{
			m_running = false;
			if (m_workerThread.joinable())
				m_workerThread.join();
		}

		LogThread& operator=(const LogThread&) = delete;
		LogThread& operator=(LogThread&&) = delete;

		void addTask(LogEntry&& entry, std::function<void(const LogEntry&)> sinkFunc, TaskToken& token)
		{
			if (m_running)
			{
				token.taskQueued();
				m_taskQueue.enqueue({ std::move(entry), sinkFunc, token });
			}
		}

	private:
		struct Task
		{
			LogEntry entry;
			std::function<void(const LogEntry&)> sinkFunc;
			TaskToken& token;
		};

		LogThread() : Singleton<LogThread>()
		{
			m_workerThread = std::thread(&LogThread::processTasks, this);
		}

		void processTasks()
		{
			while (m_running)
			{
				auto [entry, sink, token] = m_taskQueue.dequeue();
				sink(entry);
				token.taskFinished();
			}
		}

		ThreadSafeQueue<Task> m_taskQueue;

		std::thread m_workerThread;
		std::atomic<bool> m_running = true;

		friend void startLogThread();
	};
} // namespace Aegix::Log