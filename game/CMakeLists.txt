project(game)

file(GLOB SOURCES
        game.cpp
        app.cpp
        Render/GameRender.cpp
        Gui/GameGui.cpp
        Gui/Notify.cpp
        Scenes/MainMenu/MainMenu.cpp
        Scenes/MainMenu/Gui/MenuGui.cpp

        Scenes/World/World.cpp
        Scenes/World/Gui/WorldGui.cpp
        Scenes/World/Gui/HUD/HUDLayout.cpp
        Scenes/World/Gui/Layout.cpp
        Scenes/World/Gui/HUD/SlotsLayout.cpp
        Scenes/World/Gui/HUD/SlotsLayout.hpp
        Scenes/World/Gui/HUD/SlotsContent.cpp
        Scenes/World/Gui/HUD/SlotsContent.hpp
        )
set(GAME_INCLUDE ${PROJECT_SOURCE_DIR})
set(GAME_INCLUDE ${GAME_INCLUDE} PARENT_SCOPE)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} mt::engine)
target_include_directories(${PROJECT_NAME} PUBLIC ${GAME_INCLUDE})
install(TARGETS ${PROJECT_NAME} DESTINATION bin/)
