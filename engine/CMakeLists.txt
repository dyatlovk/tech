project(engine)

#build count increment
file (STRINGS "build.in" BUILD_NO)
math(EXPR BUILD_NO "${BUILD_NO}+1")
file(WRITE "build.in" "${BUILD_NO}")

find_package(glfw3 3.3 REQUIRED) 
find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

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
  States/States.cpp
  Scenes/Scenes.cpp
  Guis/Gui.cpp
  Guis/Console.cpp
  )
add_library(mt::engine ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw Threads::Threads)
install(
  TARGETS 
  ${PROJECT_NAME} 
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  )
