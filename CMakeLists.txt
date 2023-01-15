cmake_minimum_required(VERSION 3.18)
project(Demo)
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)
set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
string(TIMESTAMP COMPILE_TIME "%Y-%m-%d %H:%M:%S")
set(CMAKE_REQUIRED_FLAGS "-std=c++17 -std=c11")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Set default build type
if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif ()

# Set default install path
IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    SET(CMAKE_INSTALL_PREFIX $ENV{HOME}/Games/tech2/ CACHE PATH "Install" FORCE)
ENDIF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

# Set path to project shared libraries
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# Set resources dir
set(RESOURCES_DIR ${CMAKE_INSTALL_PREFIX}/data CACHE STRING "" FORCE)
set(ROOT_DIR ${CMAKE_INSTALL_PREFIX} CACHE STRING "" FORCE)

# Uses Git to find the current git branch and commit.
execute_process(
        COMMAND git rev-parse --abbrev-ref HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
)

execute_process(
        COMMAND git log -1 --format=%h
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
)

add_subdirectory(engine)
# add_subdirectory(editor)
add_subdirectory(game)

option(BUILD_TESTS "Build unit tests" ON)
if (BUILD_TESTS)
    set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} -ggdb3")
    enable_testing()
    add_subdirectory(tests)
endif ()
