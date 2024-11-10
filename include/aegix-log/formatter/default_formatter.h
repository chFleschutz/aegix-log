#pragma once

#include "aegix-log/formatter/formatter.h"
#include "aegix-log/util.h"

namespace Aegix::Log
{
	class DefaultFormatter : public Formatter
	{
	public:
		std::string format(const LogEntry& entry) override
		{
			auto localTime = std::chrono::current_zone()->to_local(entry.time());
			auto ms = localTime.time_since_epoch() % std::chrono::seconds(60);
			float seconds = std::chrono::duration<float>(ms).count();

			return std::format("{:%Y-%m-%d %H:%M:}{:0>6.3f} | {:<5} | {}",
				localTime,
				seconds,
				toString(entry.severity()),
				entry.message());
		}
	};
} // namespace Aegix::Log