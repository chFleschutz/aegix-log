cmake_minimum_required(VERSION 3.28)

project(aegix-log)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(AEGIX_LOG_BUILD_TESTS "Build tests for Aegix::Log" OFF)

add_library(${PROJECT_NAME} STATIC)
add_library(Aegix::Log ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        src/logger.cpp
    PUBLIC
        src/log.h
        src/log_entry.h
        src/log_sink.h
        src/logger.h
        src/sinks/console_sink.h
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Always build tests if this is the root project
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(AEGIX_LOG_BUILD_TESTS ON)
endif()

if(AEGIX_LOG_BUILD_TESTS)
    add_subdirectory(test)
endif()