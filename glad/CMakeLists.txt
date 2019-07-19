cmake_minimum_required (VERSION 2.6)


add_library(glad SHARED include/glad/glad.h src/glad.c)
target_compile_definitions(glad PUBLIC GLAD_GLAPI_EXPORT PRIVATE GLAD_GLAPI_EXPORT_BUILD)
target_include_directories(glad PUBLIC include/)
