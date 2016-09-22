cmake_minimum_required(VERSION 2.8)

project(sampleF16c)

add_executable(withoutF16c main.cpp)

set_source_files_properties(f16.cpp PROPERTIES COMPILE_FLAGS "-mf16c" )

add_executable(withF16c f16.cpp)
