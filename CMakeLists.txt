cmake_minimum_required(VERSION 3.16)
project(cfixed)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-O1)

add_executable(cfixed benchmark.cpp)