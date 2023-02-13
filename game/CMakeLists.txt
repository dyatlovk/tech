project(game)

set(APP_LIB_DIR "${PROJECT_SOURCE_DIR}/lib/")

add_subdirectory(lib/lua)
add_subdirectory(App)

file(GLOB SOURCES game.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} mt::engine mt::game)
install(TARGETS ${PROJECT_NAME} DESTINATION bin/)
