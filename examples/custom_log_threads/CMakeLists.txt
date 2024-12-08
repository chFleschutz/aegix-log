cmake_minimum_required(VERSION 3.28)

add_executable(CustomLogThreads "main.cpp")
target_link_libraries(CustomLogThreads PRIVATE Aegix::Log)
