#include "logger.h"

#include <cassert>

namespace Aegix
{

Logger::Logger()
{
	assert(!s_instance && "Logger already initialized");
	s_instance = this;
}

Logger::~Logger()
{
	assert(s_instance);
	s_instance = nullptr;
}

Logger& Logger::instance()
{
	assert(s_instance && "Logger not initialized");
	return *s_instance;
}

} // namespace Aegix