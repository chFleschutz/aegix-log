cmake_minimum_required(VERSION 3.28)

project(aegix_log_test)

add_executable(aegix_log_test "main.cpp")
target_compile_definitions(aegix_log_test PRIVATE WORKING_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}")
