project(editor)

file(GLOB SOURCES 
  src/editor.cpp 
  src/app.cpp
  src/EditorRender.cpp
  )
set(EDITOR_INCLUDE ${PROJECT_SOURCE_DIR}/include)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} mt::engine)
target_include_directories(${PROJECT_NAME} PUBLIC ${EDITOR_INCLUDE})
install(TARGETS ${PROJECT_NAME} DESTINATION bin/)
