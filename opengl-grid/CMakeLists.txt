cmake_minimum_required (VERSION 2.6)

add_executable(opengl-grid main.cpp)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(opengl-grid PRIVATE glfw)
target_link_libraries(opengl-grid PRIVATE glad)
