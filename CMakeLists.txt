cmake_minimum_required(VERSION 3.2)
project(AiBToS_Project1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "lib/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "lib/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

set(CMAKE_CXX_FLAGS "-O3 -Wall -std=c++0x -march=native")

set(SOURCE_FILES
        src/main.cpp src/Days.cpp src/Days.h)

add_executable(AiBToS_Project1 ${SOURCE_FILES})
add_executable(AiBToS_Project1_perf ${SOURCE_FILES})
target_compile_options(AiBToS_Project1_perf PRIVATE -DPERFORMANCE)

add_executable(TreeGenerator src/generator.cpp)