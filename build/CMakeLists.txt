cmake_minimum_required(VERSION 3.25)
project(winzip_native LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(winzip_native SHARED
    ../src/native/native_core.cpp
)

target_include_directories(winzip_native PRIVATE
    ../src/native
)

target_compile_definitions(winzip_native PRIVATE
    WINZIP_NATIVE_EXPORTS
)
