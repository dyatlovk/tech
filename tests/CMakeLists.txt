cmake_minimum_required(VERSION 3.18)
project(GameUnitTests)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

file(GLOB SOURCES
        main.cpp
        ../game/Gui/GameGui.hpp
        ../game/Gui/GameGui.cpp
        ../game/Scenes/World/Gui/HUD/HUDLayout.hpp
        ../game/Scenes/World/Gui/HUD/HUDLayout.cpp
        ../game/Scenes/World/Gui/HUD/SlotsLayout.hpp
        ../game/Scenes/World/Gui/HUD/SlotsLayout.cpp
        )

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${ENGINE_INCLUDE} ${GAME_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE mt::engine ${GTEST_LIBRARIES} Threads::Threads)
add_test(NAME ${PROJECT_NAME} COMMAND ${CMAKE_BINARY_DIR}/tests/${PROJECT_NAME})
