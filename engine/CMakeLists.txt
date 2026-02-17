# engine/CMakeLists.txt

if (NOT TARGET spdlog::spdlog)
    message(FATAL_ERROR "Dependency spdlog not found!")
endif()

add_library(core STATIC
    defines.cpp             # for global definitions like export macros and common includes
    # Core engine files
    core/Application.cpp
    core/Log.cpp
    # Utility files
    utils/Clock.cpp         
    # platform-specific files 
    platform/Platform.cpp
    # rendering files
    render/Renderer.cpp
    render/Device.cpp
    # resource management files
    resources/Shader.cpp
    resources/Texture.cpp
    resources/Mesh.cpp
)

target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/utils   # expose utility header
    ${CMAKE_CURRENT_SOURCE_DIR}/platform
    ${CMAKE_CURRENT_SOURCE_DIR}/resources
)

# Link external dependencies for core
target_link_libraries(core PUBLIC
    glad
    glfw
    glm
    stb
    spdlog::spdlog
)

if (WIN32)
    target_link_libraries(core PUBLIC opengl32)
endif()
