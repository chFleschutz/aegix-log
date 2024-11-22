#pragma once

#include "aegix-log/formatter/formatter.h"
#include "aegix-log/util.h"

namespace Aegix::Log
{
	class DefaultFormatter : public Formatter
	{
	public:
		auto format(const LogEntry& entry) -> std::string override 
		{
			auto localTime = std::chrono::current_zone()->to_local(entry.time);
			auto ms = localTime.time_since_epoch() % std::chrono::seconds(60);
			float seconds = std::chrono::duration<float>(ms).count();

			// Convert thread id to printable string
			std::ostringstream threadId;
			threadId << entry.threadId;

			// Format: YYYY-MM-DD HH:MM:SS.sss [ThreadID] Severity | Message
			return std::format("{:%Y-%m-%d %H:%M:}{:0>6.3f} [{:0>5}] {:<5} | {}",
				localTime,
				seconds,
				threadId.str(),
				toString(entry.severity),
				entry.message);
		}
	};
} // namespace Aegix::Log