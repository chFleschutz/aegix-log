#include "log.h"

#include <filesystem>
#include <string>

int main()
{
	Aegix::Log::init();

	LOG_CRITICAL <<"This is a critical message\n";
	LOG_WARNING << "This is a warning message\n";
	LOG_INFO << "This is an info message\n";
	LOG_DEBUG << "This is a debug message\n";
	LOG_TRACE << "This is a trace message\n";

	LOG_INFO;
	LOG_INFO << "\n";
	LOG_INFO << std::setw(20) << std::setfill('-') << " 20->\n";
	LOG_INFO << "The answer is " << 42 << " and pi is " << 3.14159 << "!\n";
	LOG_INFO << std::string("Im a string") << " and " << std::filesystem::path("im/a/path") << "\n";
	LOG_INFO << std::setw(10) << std::setfill('0') << 42 << " is the answer\n";
	LOG_INFO << std::setprecision(1) << 3.14159 << " is pi\n";

	return 0;
}