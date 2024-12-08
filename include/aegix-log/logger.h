#pragma once

#include "aegix-log/formatter/default_formatter.h"
#include "aegix-log/helper/singleton.h"
#include "aegix-log/log_entry.h"
#include "aegix-log/log_thread.h"
#include "aegix-log/sinks/log_sink.h"

#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <type_traits>
#include <vector>

namespace Aegix::Log
{
	template <int ID>
	class Logger : public Singleton<Logger<ID>>
	{
	public:
		~Logger()
		{
			if (m_lastTask.valid())
				m_lastTask.wait();
		}

		void log(LogEntry entry)
		{
#ifndef AEGIX_LOG_DISABLE_LOGGING
			if (entry.severity < m_severityThreshold)
				return;

			if (m_logThread)
			{
				m_lastTask = m_logThread->addTask(std::move(entry), std::bind_front(&Logger::write, this));
			}
			else
			{
				write(entry);
			}
#endif
		}

		template <typename... Args>
		void log(Severity severity, std::format_string<Args...> fmt, Args&&... args)
		{
#ifndef AEGIX_LOG_DISABLE_LOGGING
			log({ severity,
				std::chrono::system_clock::now(),
				std::this_thread::get_id(),
				std::format(fmt, std::forward<Args>(args)...) });
#endif
		}

		template <typename... Args>
		void fatal(std::format_string<Args...> fmt, Args&&... args)
		{
#ifndef AEGIX_LOG_DISABLE_FATAL
			log(Severity::Fatal, fmt, std::forward<Args>(args)...);
#endif
		}

		template <typename... Args>
		void warn(std::format_string<Args...> fmt, Args&&... args)
		{
#ifndef AEGIX_LOG_DISABLE_WARN
			log(Severity::Warn, fmt, std::forward<Args>(args)...);
#endif
		}

		template <typename... Args>
		void info(std::format_string<Args...> fmt, Args&&... args)
		{
#ifndef AEGIX_LOG_DISABLE_INFO
			log(Severity::Info, fmt, std::forward<Args>(args)...);
#endif
		}

		template <typename... Args>
		void debug(std::format_string<Args...> fmt, Args&&... args)
		{
#ifndef AEGIX_LOG_DISABLE_DEBUG
			log(Severity::Debug, fmt, std::forward<Args>(args)...);
#endif
		}

		template <typename... Args>
		void trace(std::format_string<Args...> fmt, Args&&... args)
		{
#ifndef AEGIX_LOG_DISABLE_TRACE
			log(Severity::Trace, fmt, std::forward<Args>(args)...);
#endif
		}

		template <typename SinkType, typename FormatterType = DefaultFormatter, typename... Args>
			requires std::derived_from<SinkType, LogSink> and std::derived_from<FormatterType, Formatter>
		auto addSink(Args&&... args) -> Logger<ID>&
		{
			auto formatter = std::make_unique<FormatterType>();
			auto sink = std::make_unique<SinkType>(std::move(formatter), std::forward<Args>(args)...);
			std::lock_guard lock(m_sinkMutex);
			m_sinks.emplace_back(std::move(sink));
			return *this;
		}

		void write(const LogEntry& entry)
		{
			std::lock_guard lock(m_sinkMutex);
			for (auto& sink : m_sinks)
				sink->log(entry);
		}

		[[nodiscard]] auto severityThreshold() const -> Severity { return m_severityThreshold; }

		void setSeverityThreshold(Severity severity) { m_severityThreshold = severity; }

	private:
		explicit Logger(std::shared_ptr<LogThread> logThread, Severity severityThreshold)
			: Singleton<Logger<ID>>(), m_logThread{ std::move(logThread) },
			  m_severityThreshold{ severityThreshold }
		{
		}

		std::shared_ptr<LogThread> m_logThread;
		Severity m_severityThreshold;

		std::vector<std::unique_ptr<LogSink>> m_sinks;
		std::mutex m_sinkMutex;
		std::future<void> m_lastTask;

		template <int LoggerID>
		friend auto initLogger(std::shared_ptr<LogThread>, Severity) -> Logger<LoggerID>&;
	};

	template <int LoggerID>
	inline auto initLogger(std::shared_ptr<LogThread> logThread, Severity severityThreshold) -> Logger<LoggerID>&
	{
		static Logger<LoggerID> logger(logThread, severityThreshold);
		return logger;
	}
} // namespace Aegix::Log