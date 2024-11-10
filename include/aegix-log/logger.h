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
	template <int _LogID>
	class Logger : public Singleton<Logger<_LogID>>
	{
	public:
		void operator+=(LogEntry entry)
		{
			if (entry.severity() < m_severityThreshold)
				return;

			if (m_logThread)
			{
				*m_logThread += { std::move(entry), std::bind_front(&Logger::write, this), m_taskToken };
			}
			else
			{
				write(entry);
			}
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
		explicit Logger(std::shared_ptr<LogThread> logThread, Severity severityThreshold)
			: Singleton<Logger<_LogID>>(), m_logThread{ logThread }, m_severityThreshold{ severityThreshold }
		{
		}

		std::shared_ptr<LogThread> m_logThread;
		Severity m_severityThreshold;

		std::vector<std::unique_ptr<LogSink>> m_sinks;
		std::mutex m_sinkMutex;

		// Keep this last to ensure it's destroyed first
		Token m_taskToken;

		template <int LogID>
		friend Logger<LogID>& initLogger(std::shared_ptr<LogThread>, Severity);
	};

	template <int LogID>
	inline Logger<LogID>& initLogger(std::shared_ptr<LogThread> logThread, Severity severityThreshold)
	{
		static Logger<LogID> logger(logThread, severityThreshold);
		return logger;
	}
} // namespace Aegix::Log