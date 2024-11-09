cmake_minimum_required(VERSION 3.28)

project(aegix-log LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Options ---
option(AEGIX_LOG_BUILD_EXAMPLES "Build examples for Aegix::Log" OFF)

# Force enabling examples in root project
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(AEGIX_LOG_BUILD_EXAMPLES ON CACHE BOOL "Force enable examples in root project" FORCE)
endif()

# --- Library ---
add_library(${PROJECT_NAME} INTERFACE)
add_library(Aegix::Log ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

# --- Examples ---
if(AEGIX_LOG_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
