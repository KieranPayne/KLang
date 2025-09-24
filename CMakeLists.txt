cmake_minimum_required(VERSION 3.28)
project(CCompiler LANGUAGES CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp)
add_executable(CCompiler ${SOURCES})


add_definitions(-w)
