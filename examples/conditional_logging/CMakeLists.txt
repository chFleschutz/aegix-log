cmake_minimum_required(VERSION 3.28)

add_executable(ConditionalLogging "main.cpp")
target_link_libraries(ConditionalLogging PRIVATE Aegix::Log)
