cmake_minimum_required(VERSION 3.27)

project(
    RayTracer
    VERSION 0.1
    LANGUAGES CXX
)

# Includes the src directory so executable can include files inside of it
include_directories(src)

# The directory the executable is stored in
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/raytracer)