#./CMakeLists.txt

cmake_minimum_required(VERSION 3.20)
project(OranGE LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
elseif(UNIX)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

# engine subdirectory
add_subdirectory(OranGE)

# Add projects subdirectories
add_subdirectory(sandbox)