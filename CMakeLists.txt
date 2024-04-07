cmake_minimum_required(VERSION 3.18)

if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

set(CMAKE_CXX_STANDARD 17)
project(leetcode)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
enable_testing()

include(cmake/catch2.cmake)

add_subdirectory(src)
