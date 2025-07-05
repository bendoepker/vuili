cmake_minimum_required(VERSION 3.25)

project(vuili)

# Avoid function argument expansion
cmake_policy(SET CMP0054 NEW)

# Honor Visibility Policies by All Targets
cmake_policy(SET CMP0063 NEW)

# CMake tool directory
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_tools)

if(NOT DEFINED build_tests AND PROJECT_IS_TOP_LEVEL)
    set(build_tests ON)
endif()

# Add output files to the same directory
include(CMakeOutputDirectory)

# Setup the library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Build tests
if(${build_tests})
    message(STATUS "Building test projects")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()
