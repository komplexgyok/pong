# Minimum CMake version
cmake_minimum_required(VERSION 3.17)

# Project name
project(glad)

# Path aliases
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Source file to compile
set(SOURCE ${SOURCE_DIR}/glad.c)

# Add a library target
add_library(${PROJECT_NAME} ${SOURCE})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
