#pragma once

#include "aegix-log/helper/singleton.h"
#include "aegix-log/helper/thread_safe_queue.h"
#include "aegix-log/log_entry.h"
#include "aegix-log/sinks/log_sink.h"

#include <atomic>
#include <cassert>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

namespace Aegix::Log
{
	template <int ID>
	class Logger : public Singleton<Logger<ID>>
	{
	public:
		~Logger()
		{
			m_running = false;
			if (m_workerThread.joinable())
				m_workerThread.join();
		}

		void operator+=(LogEntry&& entry)
		{
			if (entry.severity() < m_severityThreshold)
				return;

			m_logQueue.enqueue(std::move(entry));
		}

		template <typename T, typename... Args>
		Logger& addSink(Args&&... args)
		{
			static_assert(std::is_base_of_v<LogSink, T>, "T must derive from LogSink");
			std::lock_guard lock(m_sinkMutex);
			m_sinks.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
			return *this;
		}

		Severity severityThreshold() const { return m_severityThreshold; }

		void setSeverityThreshold(Severity severity) { m_severityThreshold = severity; }

	private:
		explicit Logger(Severity severityThreshold)
			: Singleton<Logger<ID>>(), m_severityThreshold{ severityThreshold }
		{
			m_workerThread = std::thread(&Logger::processLogQueue, this);
		}

		void processLogQueue()
		{
			while (m_running || !m_logQueue.empty())
			{
				auto entry = m_logQueue.dequeue();
				std::lock_guard lock(m_sinkMutex);
				for (const auto& sink : m_sinks)
				{
					sink->log(entry);
				}
			}
		}

		Severity m_severityThreshold;

		std::vector<std::unique_ptr<LogSink>> m_sinks;
		std::mutex m_sinkMutex;

		ThreadSafeQueue<LogEntry> m_logQueue;
		std::thread m_workerThread;
		std::atomic<bool> m_running = true;

		template <int N>
		friend Logger<N>& init(Severity);
	};
} // namespace Aegix::Log