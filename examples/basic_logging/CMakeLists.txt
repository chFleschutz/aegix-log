cmake_minimum_required(VERSION 3.28)

add_executable(BasicLogging "main.cpp")
target_link_libraries(BasicLogging PRIVATE Aegix::Log)
