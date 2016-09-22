cmake_minimum_required(VERSION 2.8)

project(sampleF16c)

set(CMAKE_CXX_FLAGS "-mf16c")

add_executable(withoutF16c main.cpp)

add_executable(withF16c f16.cpp)
