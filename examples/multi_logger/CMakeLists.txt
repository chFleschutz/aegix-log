cmake_minimum_required(VERSION 3.28)

add_executable(MultiLogger "main.cpp")
target_link_libraries(MultiLogger PRIVATE Aegix::Log)
