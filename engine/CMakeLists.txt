project(engine)

#build count increment
file (STRINGS "build.in" BUILD_NO)
math(EXPR BUILD_NO "${BUILD_NO}+1")
file(WRITE "build.in" "${BUILD_NO}")

find_package(glfw3 3.3 REQUIRED) 
find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)
find_package(Freetype REQUIRED)

configure_file(Config.hpp.in "${PROJECT_SOURCE_DIR}/Config.hpp" @ONLY)
configure_file(Settings.in "${RESOURCES_DIR}/Engine/Settings.ini" @ONLY)

add_library(${PROJECT_NAME} SHARED 
  Engine/Engine.cpp
  Engine/CVars.cpp
  Engine/Log.cpp
  Engine/Commands.cpp
  Engine/IniParser.cpp
  Devices/Window.cpp
  Devices/Keyboard.cpp
  Graphics/Graphics.cpp
  Graphics/Texture.cpp
  Inputs/Input.cpp
  Inputs/Buttons/KeyboardInputButton.cpp
  third_party/imgui/imgui.cpp
  third_party/imgui/imgui_demo.cpp
  third_party/imgui/imgui_draw.cpp
  third_party/imgui/imgui_tables.cpp
  third_party/imgui/imgui_widgets.cpp
  third_party/imgui/imgui_impl_opengl3.cpp
  third_party/imgui/imgui_impl_glfw.cpp
  third_party/imgui/imgui_stdlib.cpp
  third_party/imgui/freetype/imgui_freetype.cpp
  States/States.cpp
  Scenes/Scenes.cpp
  Resources/ResourcesManager.cpp
  Guis/Gui.cpp
  Guis/Console.cpp
  Guis/Font.cpp
  Maths/ElapsedTime.cpp
  Utils/ThreadPool.cpp
  )
set(ENGINE_INCLUDE ${PROJECT_SOURCE_DIR})
set(ENGINE_INCLUDE ${ENGINE_INCLUDE} PARENT_SCOPE)
add_library(mt::engine ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${ENGINE_INCLUDE} ${FREETYPE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw Threads::Threads ${FREETYPE_LIBRARIES})
install(
  TARGETS 
  ${PROJECT_NAME} 
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  )
