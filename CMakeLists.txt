# Minimum CMake version
cmake_minimum_required(VERSION 3.17)

# Project name
project(pong)

# Use the C++17 standard
set(CMAKE_CXX_STANDARD 17)

# Path aliases
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

# List of source files to compile
set(SOURCE
    ${SOURCE_DIR}/main.cpp
)

# Add an executable target
add_executable(${PROJECT_NAME} ${SOURCE})
