#pragma once

#include "aegix-log/log.h"
#include "aegix-log/log_sink.h"

#include <cassert>
#include <filesystem>
#include <fstream>

namespace Aegix
{
	class FileSink : public LogSink
	{
	public:
		FileSink(const std::filesystem::path& filepath)
		{
			if (filepath.has_parent_path())
			{
				std::error_code error;
				std::filesystem::create_directories(filepath.parent_path(), error);
				if (error)
				{
					assert(false && "Failed to create directory for log-file");
					LOG_CRITICAL << "Failed to create directory for log-file: " << filepath.parent_path()
								 << " Error: " << error.message();
				}
			}

			m_file.open(filepath, std::ios::out | std::ios::trunc);
			if (!m_file.is_open())
			{
				assert(false && "Failed to open log-file");
				LOG_CRITICAL << "Failed to open log-file: " << filepath;
			}
		}

		~FileSink() override
		{
			if (m_file.is_open())
			{
				m_file.flush();
				m_file.close();
			}
		}

		void log(const LogEntry& entry) override
		{
			if (!m_file.is_open())
				return;

			auto localTime = std::chrono::current_zone()->to_local(entry.time());
			auto ms = localTime.time_since_epoch() % std::chrono::seconds(60);
			float seconds = std::chrono::duration<float>(ms).count();

			m_file << std::format("{:%Y-%m-%d %H:%M:}{:0>6.3f}", localTime, seconds) << " " // Time
					  << std::left << std::setw(8) << toString(entry.severity()) << " " // Severity
					  << entry.message() << "\n";										// Message
		}

	private:
		std::ofstream m_file;
	};
} // namespace Aegix