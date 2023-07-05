cmake_minimum_required(VERSION 3.15)
project(Calculator)

set(CMAKE_CXX_STANDARD 11)

# Add Google Test as an external project
include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0
)

FetchContent_MakeAvailable(googletest)

# Add your executable
add_executable(Calculator calculator.cpp)
add_executable(CalculatorTest tests/calculator.cpp)

# Link against Google Test
target_link_libraries(Calculator gtest gtest_main)
target_link_libraries(CalculatorTest gtest gtest_main)

# Add test
enable_testing()

add_test( NAME CalculatorTest COMMAND CalculatorTest )

set_property(TARGET CalculatorTest PROPERTY FOLDER "Tests")