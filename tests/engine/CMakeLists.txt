cmake_minimum_required(VERSION 3.18)
project(EngineUnitTests)

configure_file(TestConfig.hpp.in "${PROJECT_SOURCE_DIR}/TestConfig.hpp" @ONLY)

file(GLOB SOURCES
        main.cpp
        Engine/CVarsTest.cpp
        Engine/Files/FileTest.cpp
        Engine/Files/FileGltfTest.cpp
        Engine/Files/FileEntitiesTest.cpp
        Engine/Resources/ResourcesManagerTest.cpp
        Engine/Maths/TransformationTest.cpp
        Engine/Network/Sockets/ServerSocketTest.cpp
        Engine/Network/Sockets/RequestTest.cpp
        Engine/Scripts/LuaBindTest.cpp
        Engine/Events/EventsTest.cpp
        )
set(TEST_INCLUDE .)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${ENGINE_INCLUDE} ${TEST_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE mt::engine ${GTEST_LIBRARIES})
add_test(NAME ${PROJECT_NAME} COMMAND ${CMAKE_BINARY_DIR}/tests/engine/${PROJECT_NAME})
