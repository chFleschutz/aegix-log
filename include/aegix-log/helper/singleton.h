#pragma once

#include <cassert>

namespace Aegix::Log
{
	/// @brief Base class for singletons
	/// @tparam T Class type of the derived class for casting the instance
	/// @note This class is missing a virtual destructor, so its not intended to be used as a polymorphic base class
	template <typename T>
	class Singleton
	{
	public:
		~Singleton()
		{
			assert(s_instance);
			s_instance = nullptr;
		}

		Singleton(const Singleton&) = delete;
		Singleton(Singleton&&) = delete;

		auto operator=(const Singleton&) -> Singleton& = delete;
		auto operator=(Singleton&&) -> Singleton& = delete;

		static auto instance() -> T& { return *s_instance; }

	protected:
		Singleton()
		{
			assert(!s_instance && "Singleton already initialized");
			s_instance = static_cast<T*>(this);
		}

		inline static T* s_instance = nullptr;
	};
} // namespace Aegix