cmake_minimum_required (VERSION 2.6)

add_library(glad STATIC include/glad/glad.h src/glad.c)
target_include_directories(glad PUBLIC include/)
