cmake_minimum_required(VERSION 3.13)
project(logger)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(include/appenders)
include_directories(include/formatters)
add_library(liblogger src/main.cpp)
set_target_properties(liblogger PROPERTIES PREFIX "")
target_include_directories(liblogger PUBLIC include include/appenders include/formatters)
add_executable(logger
        src/main.cpp
        src/handler.cpp)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(include)
add_executable(
        utils_test
        tests/utils_test.cpp)
target_link_libraries(
        utils_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(utils_test)
