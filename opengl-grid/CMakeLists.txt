cmake_minimum_required (VERSION 2.6)

# define target
add_executable(opengl-grid src/main.cpp)

# set include directories
target_include_directories(opengl-grid PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# find packages
find_package(glfw3 3.3 REQUIRED)
find_package(glm CONFIG REQUIRED)

# link packages
target_link_libraries(opengl-grid PRIVATE glfw)
target_link_libraries(opengl-grid PRIVATE glad)
target_link_libraries(opengl-grid PRIVATE glm)

# set target properties
target_compile_features(opengl-grid PRIVATE cxx_std_17)
