#pragma once

#include "aegix-log/format.h"
#include "aegix-log/log.h"
#include "aegix-log/sinks/log_sink.h"

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
					LOG_FATAL << "Failed to create directory for log-file: " << filepath.parent_path()
								 << " Error: " << error.message();
				}
			}

			m_file.open(filepath, std::ios::out | std::ios::trunc);
			if (!m_file.is_open())
			{
				assert(false && "Failed to open log-file");
				LOG_FATAL << "Failed to open log-file: " << filepath;
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

			m_file << Log::formatText(entry) << "\n";
		}

	private:
		std::ofstream m_file;
	};
} // namespace Aegix