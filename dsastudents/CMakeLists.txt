cmake_minimum_required(VERSION 3.10)
project(dsaAssignment1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Automatically include all files in 'include/list' and 'include/ann'
file(GLOB_RECURSE LIST_HEADERS include/list/*.h)
file(GLOB_RECURSE ANN_HEADERS include/ann/*.h)

# You can also do the same for source files if needed:
file(GLOB_RECURSE LIST_SOURCES src/list/*.cpp)
file(GLOB_RECURSE ANN_SOURCES src/ann/*.cpp)

# Add all headers and sources to the executable
add_executable(dsaAssignment1 main.cpp ${LIST_HEADERS} ${ANN_HEADERS} ${LIST_SOURCES} ${ANN_SOURCES})
