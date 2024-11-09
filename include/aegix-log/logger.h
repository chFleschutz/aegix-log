#pragma once

#include "aegix-log/helper/singleton.h"
#include "aegix-log/log_entry.h"
#include "aegix-log/log_thread.h"
#include "aegix-log/sinks/log_sink.h"

#include <memory>
#include <mutex>
#include <vector>

namespace Aegix::Log
{

	template <int ID>
	class Logger : public Singleton<Logger<ID>>
	{
	public:
		friend class Singleton<Logger<ID>>;

		void operator+=(LogEntry&& entry)
		{
			if (entry.severity() < m_severityThreshold)
				return;

			LogThread::instance().addTask(
				std::move(entry),
				[this](const LogEntry& entry) { write(entry); },
				m_taskToken);
		}

		template <typename T, typename... Args>
		Logger& addSink(Args&&... args)
		{
			static_assert(std::is_base_of_v<LogSink, T>, "T must derive from LogSink");
			std::lock_guard lock(m_sinkMutex);
			m_sinks.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
			return *this;
		}

		void write(const LogEntry& entry)
		{
			std::lock_guard lock(m_sinkMutex);
			for (auto& sink : m_sinks)
				sink->log(entry);
		}

		Severity severityThreshold() const { return m_severityThreshold; }

		void setSeverityThreshold(Severity severity) { m_severityThreshold = severity; }

	private:
		explicit Logger(Severity severityThreshold)
			: Singleton<Logger<ID>>(), m_severityThreshold{ severityThreshold }
		{
		}

		Severity m_severityThreshold;

		std::vector<std::unique_ptr<LogSink>> m_sinks;
		std::mutex m_sinkMutex;

		// Keep this last to ensure it's destroyed first
		TaskToken m_taskToken;

		template <int N>
		friend Logger<N>& init(Severity);
	};
} // namespace Aegix::Log