cmake_minimum_required(VERSION 2.8)

project(sampleF16c)

if((X86 OR X86_64) AND NOT MSVC AND ENABLE_AVX)
  set(CMAKE_CXX_FLAGS "-mf16c")
endif()

add_executable(withoutF16c main.cpp)

add_executable(withF16c f16.cpp)
