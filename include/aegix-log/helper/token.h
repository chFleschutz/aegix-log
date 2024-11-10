#pragma once

#include <condition_variable>
#include <mutex>

namespace Aegix::Log
{
	/// @brief Token class for ensuring no pending resources are left
	/// @note This class destructor will block until all pending resources are released
	class Token
	{
	public:
		Token() = default;
		Token(const Token&) = delete;
		Token(Token&&) = delete;
		~Token() { waitPending(); }

		Token& operator=(const Token&) = delete;
		Token& operator=(Token&&) = delete;

		void waitPending()
		{
			std::unique_lock lock(m_queueMutex);
			m_taskAvailable.wait(lock, [this] { return m_pendingCount == 0; });
		}

		void increment()
		{
			std::lock_guard lock(m_queueMutex);
			m_pendingCount++;
		}

		void decrement()
		{
			std::lock_guard lock(m_queueMutex);
			m_pendingCount--;
			if (m_pendingCount == 0)
				m_taskAvailable.notify_all();
		}

	private:
		uint32_t m_pendingCount = 0;
		std::condition_variable m_taskAvailable;
		std::mutex m_queueMutex;
	};
}