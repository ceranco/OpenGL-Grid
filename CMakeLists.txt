cmake_minimum_required (VERSION 2.6)
project (OpenGL-Grid)

add_executable(opengl-grid main.cpp)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

add_subdirectory(glad/)

include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(opengl-grid PRIVATE ${GLFW_LIBRARIES} PRIVATE glad)


