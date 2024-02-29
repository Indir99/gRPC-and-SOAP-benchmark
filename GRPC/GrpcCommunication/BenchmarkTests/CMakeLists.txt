cmake_minimum_required(VERSION 3.10)
project(BenchmarkTests)

# Find Google Benchmark package
find_package(benchmark REQUIRED)

# Add executable for your benchmark tests
add_executable(BenchmarkTests benchmark_tests.cpp)

# Include directories for your project
target_include_directories(BenchmarkTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Server ${CMAKE_CURRENT_SOURCE_DIR}/../Client)

# Link your benchmark tests with Google Benchmark and any other necessary libraries
target_link_libraries(BenchmarkTests PRIVATE benchmark::benchmark myproto)
