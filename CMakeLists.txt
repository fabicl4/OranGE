#./CMakeLists.txt

cmake_minimum_required(VERSION 3.20)
project(OranGE LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add projects subdirectories
add_subdirectory(OranGE)
add_subdirectory(sandbox)