project(engine)

#build count increment
file (STRINGS "build.in" BUILD_NO)
math(EXPR BUILD_NO "${BUILD_NO}+1")
file(WRITE "build.in" "${BUILD_NO}")

find_package(glfw3 3.3 REQUIRED) 
find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)
find_package(Freetype REQUIRED)
find_package(GLEW REQUIRED)

configure_file(Config.hpp.in "${PROJECT_SOURCE_DIR}/Config.hpp" @ONLY)
configure_file(Settings.in "${RESOURCES_DIR}/Engine/Settings.ini" @ONLY)

add_subdirectory(third_party/lua)

add_library(${PROJECT_NAME} SHARED 
  Engine/Engine.cpp
  Engine/CVars.cpp
  Engine/Log.cpp
  Engine/Commands.cpp
  Engine/IniParser.cpp
  Engine/Events.cpp
  Devices/Window.cpp
  Devices/Keyboard.cpp
  Devices/Mouse.cpp
  Graphics/Graphics.cpp
  Graphics/Texture.cpp
  Graphics/Shader.cpp
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
  Scenes/SceneStructure.cpp
  Scenes/EntityManager.cpp
  Scenes/Entity.cpp
  Scenes/Components/Transform.cpp
  Resources/ResourcesManager.cpp
  Guis/Gui.cpp
  Guis/Console.cpp
  Guis/Font.cpp
  Maths/ElapsedTime.cpp
  Utils/ThreadPool.cpp
  Files/File.cpp
  Files/FileGltf.cpp
  Files/FileEntities.cpp
  Models/Model.cpp
  Models/Mesh.cpp
  Models/Material.cpp
  Light/Light.cpp
  Network/Sockets/ServerSocket.cpp
  Network/Sockets/ClientSocket.cpp
  Scripts/Lua/LuaBind.cpp
  )
set(ENGINE_INCLUDE ${PROJECT_SOURCE_DIR})
set(ENGINE_INCLUDE ${ENGINE_INCLUDE} PARENT_SCOPE)
add_library(mt::engine ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${ENGINE_INCLUDE} ${FREETYPE_INCLUDE_DIRS} {$LUA_INCLUDE})
target_link_libraries(${PROJECT_NAME} OpenGL::GL GLEW glfw Threads::Threads ${FREETYPE_LIBRARIES} mt::engine::lua)
install(
  TARGETS 
  ${PROJECT_NAME} 
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  )
