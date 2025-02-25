# Specify the minimum version for CMake
cmake_minimum_required (VERSION 3.22.1)

# Set the project name
project(CSVReader)

# Add the executable
add_executable(csv_reader csv_reader.c)

#install the helloworld program system-wide
install(TARGETS csv_reader)

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}")

#add_executable(student_course_info ${PROJECT_SOURCE_DIR}/csv_reader.c)
