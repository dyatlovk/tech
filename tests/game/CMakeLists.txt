cmake_minimum_required(VERSION 3.18)
project(GameUnitTests)

file(GLOB SOURCES
        main.cpp
        Scenes/World/Gui/HUD/HUDLayoutTest.cpp
        Fixtures/HUDLayoutFixture.hpp
        ../../game/Scenes/World/Gui/HUD/HUDLayout.hpp
        ../../game/Scenes/World/Gui/HUD/HUDLayout.cpp
        ../../game/Scenes/World/Gui/HUD/SlotsLayout.cpp
        ../../game/Scenes/World/Gui/HUD/SlotsLayout.hpp
        )
set(TEST_INCLUDE .)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${GAME_INCLUDE} ${TEST_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE mt::engine ${GTEST_LIBRARIES})
add_test(NAME ${PROJECT_NAME} COMMAND ${CMAKE_BINARY_DIR}/tests/game/${PROJECT_NAME})
