cmake_minimum_required(VERSION 3.18)
project(GameUnitTests)

configure_file(Config.hpp.in "${PROJECT_SOURCE_DIR}/Config.hpp" @ONLY)

file(GLOB SOURCES
        main.cpp
        Scenes/World/Gui/HUD/HUDLayoutTest.cpp
        Scenes/World/Client/CommunicationTest.cpp
        Scripts/LuaBindTest.cpp
        )
set(TEST_INCLUDE .)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${GAME_INCLUDE} ${TEST_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE mt::engine mt::game ${GTEST_LIBRARIES})
add_test(NAME ${PROJECT_NAME} COMMAND ${CMAKE_BINARY_DIR}/tests/game/${PROJECT_NAME})
