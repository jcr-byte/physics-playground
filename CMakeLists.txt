cmake_minimum_required(VERSION 3.16)

# Support vcpkg for package management (optional - set CMAKE_TOOLCHAIN_FILE if vcpkg is installed elsewhere)
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if(EXISTS "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
        set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "vcpkg toolchain file" FORCE)
    endif()
endif()

project(physics_playground LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(physics_playground
    src/main.cpp
    src/core/EventHandler.cpp
    src/entities/Mass.cpp
    src/scene/Gravity.cpp
    $<$<PLATFORM_ID:Windows>:assets/resources.rc>
)

target_compile_options(physics_playground PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

# Enable static linking for clean distribution
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 3 COMPONENTS System Window Graphics REQUIRED)

target_link_libraries(physics_playground PRIVATE
    SFML::System
    SFML::Window
    SFML::Graphics
)

# For Windows static builds
if(WIN32)
    target_link_libraries(physics_playground PRIVATE 
        opengl32
        winmm
        gdi32
        ws2_32
    )
    target_link_options(physics_playground PRIVATE /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup)
endif()