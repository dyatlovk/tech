project(game)

file(GLOB SOURCES 
  game.cpp 
  app.cpp
  Render/GameRender.cpp
  Scenes/GameScene.cpp
  )
set(GAME_INCLUDE ${PROJECT_SOURCE_DIR}/include)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} mt::engine)
target_include_directories(${PROJECT_NAME} PUBLIC ${GAME_INCLUDE})
install(TARGETS ${PROJECT_NAME} DESTINATION bin/)
