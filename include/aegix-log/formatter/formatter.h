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

		Formatter& operator=(const Formatter&) = delete;
		Formatter& operator=(Formatter&&) = delete;

		virtual std::string format(const LogEntry& entry) = 0;
	};
} // namespace Aegix::Log