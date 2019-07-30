cmake_minimum_required (VERSION 2.6)

add_library(glad STATIC src/glad.c)
target_include_directories(glad PUBLIC include/)
target_link_libraries(glad PUBLIC ${CMAKE_DL_LIBS})
