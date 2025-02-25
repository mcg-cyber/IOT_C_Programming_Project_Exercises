# Specify the minimum version for CMake
cmake_minimum_required (VERSION 3.22.1)

# Set the project name
project(PranscriptPrinter)

# Add the executable
add_executable(transcript_printer transcript_printer.c)

#install the helloworld program system-wide
install(TARGETS transcript_printer)

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}")

#add_executable(student_course_info ${PROJECT_SOURCE_DIR}/transcript_printer.c)
