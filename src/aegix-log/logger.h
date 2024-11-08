#pragma once

#include "aegix-log/log_entry.h"
#include "aegix-log/log_sink.h"

#include <memory>
#include <vector>
#include <cassert>

namespace Aegix
{
	template<int ID>
	class Logger
	{
	public:
		explicit Logger(Severity severityThreshold) : m_severityThreshold{ severityThreshold }
		{
			assert(!s_instance && "Logger already initialized");
			s_instance = this;
		}

		Logger(const Logger&) = delete;
		~Logger()
		{
			assert(s_instance);
			s_instance = nullptr;
		}


		Logger& operator=(const Logger&) = delete;

		void operator+=(LogEntry& entry)
		{
			if (entry.severity() < m_severityThreshold)
				return;

			for (const auto& sink : m_sinks)
			{
				sink->log(entry);
			}
		}

		template <typename T, typename... Args>
		Logger& addSink(Args&&... args)
		{
			static_assert(std::is_base_of_v<LogSink, T>, "T must derive from LogSink");
			m_sinks.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
			return *this;
		}

		static Logger& instance()
		{
			assert(s_instance && "Logger not initialized");
			return *s_instance;
		}

		Severity severityThreshold() const { return m_severityThreshold; }

		void setSeverityThreshold(Severity severity) { m_severityThreshold = severity; }

	private:
		inline static Logger* s_instance = nullptr;

		Severity m_severityThreshold;
		std::vector<std::unique_ptr<LogSink>> m_sinks;
	};
} // namespace Aegix