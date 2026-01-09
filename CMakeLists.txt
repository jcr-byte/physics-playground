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
    src/ui/Sidebar.cpp
    $<$<PLATFORM_ID:Windows>:platform/windows/resources.rc>
)

target_compile_options(physics_playground PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

# Enable static linking for clean distribution
set(SFML_STATIC_LIBRARIES FALSE)
find_package(SFML 3 COMPONENTS System Window Graphics REQUIRED)

find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)

target_link_libraries(physics_playground PRIVATE
    SFML::System
    SFML::Window
    SFML::Graphics
    imgui::imgui
    ImGui-SFML::ImGui-SFML
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

# For macOS app bundle
if(APPLE)
    set_target_properties(physics_playground PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_BUNDLE_NAME "Physics Playground"
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.physicsplayground.app"
        MACOSX_BUNDLE_BUNDLE_VERSION "1.0.0"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/platform/macos/Info.plist.in"
    )
    
    # Copy assets into the app bundle
    set(ASSET_DEST "$<TARGET_BUNDLE_CONTENT_DIR:physics_playground>/Resources")
    add_custom_command(TARGET physics_playground POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${ASSET_DEST}"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/assets" "${ASSET_DEST}"
        COMMENT "Copying assets to app bundle"
    )
endif()