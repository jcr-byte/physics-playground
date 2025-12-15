cmake_minimum_required(VERSION 3.16)

project(physics_playground LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(physics_playground
    src/main.cpp
)

target_compile_options(physics_playground PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

find_package(SFML 3 COMPONENTS System Window Graphics REQUIRED)

target_link_libraries(physics_playground PRIVATE
    SFML::System
    SFML::Window
    SFML::Graphics
)