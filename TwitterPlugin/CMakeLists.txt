SET(CMAKE_CXX_COMPILER "clang")
SET(CMAKE_C_COMPILER "clang") 
SET(CMAKE_C_OUTPUT_EXTENSION ".bc")
SET(CMAKE_C_FLAGS "-emit-llvm")

cmake_minimum_required(VERSION 2.5)
project(tuxist)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")
add_subdirectory(src)

 
