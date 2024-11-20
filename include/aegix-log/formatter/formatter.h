#pragma once

#include "aegix-log/log_entry.h"

namespace Aegix::Log
{
	class Formatter
	{
	public:
		Formatter() = default;
		Formatter(const Formatter&) = delete;
		Formatter(Formatter&&) = delete;
		virtual ~Formatter() = default;

		auto operator=(const Formatter&) -> Formatter& = delete;
		auto operator=(Formatter&&) -> Formatter& = delete;

		virtual auto format(const LogEntry& entry) -> std::string = 0;
	};
} // namespace Aegix::Log