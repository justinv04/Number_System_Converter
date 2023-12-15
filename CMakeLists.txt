cmake_minimum_required(VERSION 3.15)
project(Number_System_Converter)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_VERBOSE_MAKEFILE ON)
add_compile_options(-Wall -Wextra -pedantic -g)

add_executable(nsc Converter.cpp)

set(CMAKE_VERBOSE_MAKEFILE OFF)