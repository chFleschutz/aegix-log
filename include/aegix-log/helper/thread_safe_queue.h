#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>

namespace Aegix
{
	template <typename T>
	class ThreadSafeQueue
	{
	public:
		ThreadSafeQueue() = default;
		ThreadSafeQueue(const ThreadSafeQueue&) = delete;
		ThreadSafeQueue(ThreadSafeQueue&&) = delete;
		~ThreadSafeQueue() = default;

		ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;
		ThreadSafeQueue& operator=(ThreadSafeQueue&&) = delete;

		bool empty() const
		{
			std::lock_guard lock(m_mutex);
			return m_logQueue.empty();
		}

		size_t size() const
		{
			std::lock_guard lock(m_mutex);
			return m_logQueue.size();
		}

		void clear()
		{
			std::lock_guard lock(m_mutex);
			m_logQueue.clear();
		}

		void enqueue(T entry)
		{
			std::lock_guard lock(m_mutex);
			m_logQueue.push(std::move(entry));
			m_condition.notify_one();
		}

		T dequeue()
		{
			std::unique_lock lock(m_mutex);
			m_condition.wait(lock, [this] { return !m_logQueue.empty(); });

			T entry = std::move(m_logQueue.front());
			m_logQueue.pop();
			return entry;
		}

	private:
		std::queue<T> m_logQueue;
		mutable std::mutex m_mutex;
		mutable std::condition_variable m_condition;
	};
} // namespace Aegix