# CMake version required
cmake_minimum_required(VERSION 3.16)

# Project name and language
project(tema1_paoo VERSION 1.0 LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set output directories for executables and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include the source directory for headers
include_directories(${CMAKE_SOURCE_DIR}/src)

# Define the source files
set(SOURCES
    src/main.cpp
    src/Account.cpp
)

# Create the executable
add_executable(tema1 ${SOURCES})
