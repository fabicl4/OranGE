add_executable(myapp
    main.cpp
)

# Include directories for myapp
target_include_directories(myapp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}     # Sandbox headers if any
)

# Link core static library
target_link_libraries(myapp PRIVATE core)

# Optional: set linker flags
set_target_properties(myapp PROPERTIES
    LINK_FLAGS_DEBUG "/NODEFAULTLIB:LIBCMT"
    LINK_FLAGS_RELEASE "/NODEFAULTLIB:LIBCMT"
)