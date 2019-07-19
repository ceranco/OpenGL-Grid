cmake_minimum_required (VERSION 2.6)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(glad SHARED include/glad/glad.h src/glad.c)
target_include_directories(glad PUBLIC include/)
