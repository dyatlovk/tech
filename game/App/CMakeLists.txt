project(app)
add_library(${PROJECT_NAME} SHARED 
    app.cpp
    Render/GameRender.cpp
    Gui/GameGui.cpp
    Gui/Notify.cpp
    Commands/AppCommands.cpp
    Scenes/MainMenu/MainMenu.cpp
    Scenes/MainMenu/Gui/MenuGui.cpp
    Scenes/World/World.cpp
    Scenes/World/Gui/WorldGui.cpp
    Scenes/World/Gui/HUD/HUDLayout.cpp
    Scenes/World/Gui/HUD/SlotsLayout.cpp
    Scenes/World/Gui/HUD/SlotsLayout.hpp
    Scenes/World/Gui/HUD/SlotsContent.cpp
    Scenes/World/FPSCamera.cpp
  )
set(GAME_INCLUDE ${PROJECT_SOURCE_DIR})
set(GAME_INCLUDE ${GAME_INCLUDE} PARENT_SCOPE)
add_library(mt::game ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${GAME_INCLUDE} ${APP_LIB_DIR})
target_link_libraries(${PROJECT_NAME} mt::engine)
install(
  TARGETS 
  ${PROJECT_NAME} 
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  )
