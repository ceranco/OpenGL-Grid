cmake_minimum_required (VERSION 2.6)
project (GLAD)

add_library(glad SHARED include/glad/glad.h src/glad.c)
target_include_directories(glad PUBLIC include/)
