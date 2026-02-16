# engine/CMakeLists.txt

if (NOT TARGET spdlog::spdlog)
    message(FATAL_ERROR "Dependency spdlog not found!")
endif()

add_library(core STATIC
    core/Application.cpp
    core/Log.cpp
)

target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/core
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
