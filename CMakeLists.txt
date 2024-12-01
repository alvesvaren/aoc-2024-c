cmake_minimum_required(VERSION 3.15)
project(AoC2024 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add the libcurl dependency
find_package(CURL REQUIRED)

# Add the library
add_library(lib STATIC lib.c)
target_link_libraries(lib PRIVATE CURL::libcurl)

add_subdirectory(solutions)

add_executable(main main.c)
target_link_libraries(main PRIVATE lib)
