cmake_minimum_required(VERSION 3.28)

project(aegix-log-test CXX)

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} PRIVATE Aegix::Log)
target_compile_definitions(${PROJECT_NAME} PRIVATE WORKING_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}")
