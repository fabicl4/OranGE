# OranGE/CMakeLists.txt

cmake_minimum_required(VERSION 3.20)
project(OranGECore LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# static library
add_library(OranGECore STATIC)

target_sources(OranGECore
    PRIVATE
        src/pch.cpp
        src/core/Log.cpp
        src/utils/Clock.cpp
        src/application/Application.cpp
)

target_include_directories(OranGECore
    PUBLIC
        include
)

# PCH
target_precompile_headers(OranGECore PUBLIC include/pch.h)

# external dependencies
# ------------------------
# GLFW
add_subdirectory(vendor/glfw-3.4)

# GLM (header-only)
add_library(glm INTERFACE)

target_include_directories(glm INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm
)

# STB
add_library(stb INTERFACE)

target_include_directories(stb INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb
    )

add_subdirectory(vendor/spdlog-1.17.0)

target_link_libraries(OranGECore PUBLIC
    glfw
    glm
    stb
    spdlog::spdlog
)

# TODO: Add libs: Assimp, PhysFS, entt, Box2D, OpenAL, Tracy Profiler ...