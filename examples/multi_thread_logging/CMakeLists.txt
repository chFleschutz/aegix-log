cmake_minimum_required(VERSION 3.28)

add_executable(MultiThreadLogging "main.cpp")
target_link_libraries(MultiThreadLogging PRIVATE Aegix::Log)
