cmake_minimum_required(VERSION 2.8)

project(sampleF16c)

add_executable(withoutF16c main.cpp)

if (UNIX)
    set(CMAKE_CXX_FLAGS "-mf16c")
endif()

add_executable(withF16c main.cpp)

