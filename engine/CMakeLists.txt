project(engine)

find_package(glfw3 3.3 QUIET) 
if(NOT TARGET glfw)
  FetchContent_Declare(glfw3
    URL https://github.com/glfw/glfw/archive/3.3.2.tar.gz
    URL_MD5 865e54ff0a100e9041a40429db98be0b
    )
  FetchContent_GetProperties(glfw3)
  if(NOT glfw3_POPULATED)
    FetchContent_Populate(glfw3)
    add_subdirectory(${glfw3_SOURCE_DIR} ${glfw3_BINARY_DIR})
  endif()
  set_target_properties(glfw PROPERTIES FOLDER External)
endif()

configure_file(Config.hpp.in "${PROJECT_SOURCE_DIR}/Config.hpp" @ONLY)

add_library(${PROJECT_NAME} SHARED Engine/Engine.cpp)
add_library(mt::engine ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
install(
  TARGETS 
  ${PROJECT_NAME} 
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  )
