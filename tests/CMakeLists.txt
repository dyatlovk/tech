cmake_minimum_required(VERSION 3.18)
project(UnitTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(GTest REQUIRED)

enable_testing()
add_subdirectory("game")
add_subdirectory("engine")
