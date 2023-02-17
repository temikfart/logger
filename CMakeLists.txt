cmake_minimum_required(VERSION 3.13)
project(logger)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(include/appenders)
include_directories(include/formatters)
add_executable(logger
        src/main.cpp)
