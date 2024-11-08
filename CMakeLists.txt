cmake_minimum_required(VERSION 3.28)

project(aegix_log)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Options ---
option(AEGIX_LOG_BUILD_TESTS "Build tests for Aegix::Log" OFF)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(AEGIX_LOG_BUILD_TESTS ON CACHE BOOL "Force enabling tests in root project" FORCE)
endif()

# --- Include directories ---
include_directories(src)

# --- Subdirectories ---
if(AEGIX_LOG_BUILD_TESTS)
    add_subdirectory(test)
endif()
