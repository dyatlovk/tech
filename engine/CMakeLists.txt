project(engine)

find_package(glfw3 3.3 REQUIRED) 
find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

configure_file(Config.hpp.in "${PROJECT_SOURCE_DIR}/Config.hpp" @ONLY)

add_library(${PROJECT_NAME} SHARED 
  Engine/Engine.cpp
  Devices/Window.cpp
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
