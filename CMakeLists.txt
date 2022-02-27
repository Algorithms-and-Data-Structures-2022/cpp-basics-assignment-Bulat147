# This is the top-level CMakeLists.txt file

cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(cpp_assignment CXX)

# C++ standard specification
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Helpers
include(CMakePrintHelpers)
include(cmake/MemCheck.cmake)
include(cmake/CompilerWarnings.cmake)

# Options
option(BUILD_TESTS "Build assignment tests." ON)
option(ENABLE_COMPILER_WARNINGS "Project compile warnings." ON)
option(ENABLE_MEMCHECK "Configure project for memory checking." OFF)

cmake_print_variables(CMAKE_BUILD_TYPE BUILD_TESTS ENABLE_COMPILER_WARNINGS ENABLE_MEMCHECK)

# Library
add_library(${PROJECT_NAME} STATIC src/code.cpp include/assignment/code.hpp)
target_include_directories(${PROJECT_NAME} PUBLIC include)

# Executables
add_executable(run_${PROJECT_NAME} main.cpp)
target_link_libraries(run_${PROJECT_NAME} PRIVATE ${PROJECT_NAME})

# Warnings
if (ENABLE_COMPILER_WARNINGS)
    message(STATUS "Compiler warnings: enabled")

    add_library(project_warnings INTERFACE)
    set_project_warnings(project_warnings)

    target_link_libraries(${PROJECT_NAME} PRIVATE project_warnings)
    target_link_libraries(run_${PROJECT_NAME} PRIVATE project_warnings)
endif (ENABLE_COMPILER_WARNINGS)

# Memory Check
if (ENABLE_MEMCHECK)
    enable_memcheck()
endif (ENABLE_MEMCHECK)

# Tests
if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(contrib)
    add_subdirectory(tests)
endif (BUILD_TESTS)
