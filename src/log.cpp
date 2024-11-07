#include "log.h"

namespace Aegix
{
Logger& Aegix::Log::init()
{
	static Logger logger;
	return logger;
}
} // namespace Aegix
