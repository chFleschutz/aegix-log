add_library(aegix_log_lib STATIC)
add_library(Aegix::Log ALIAS aegix_log_lib)

target_sources(aegix_log_lib PRIVATE
    "aegix-log/log.h"
    "aegix-log/log_entry.h"
    "aegix-log/log_sink.h"
    "aegix-log/logger.h"
    "aegix-log/logger.cpp"
    "aegix-log/sinks/console_sink.h"
    "aegix-log/sinks/file_sink.h"
)

target_include_directories(aegix_log_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
)
