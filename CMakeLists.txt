cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 23)

project(leetcode LANGUAGES CXX)

include(cmake/catch2.cmake)

add_subdirectory(src)

