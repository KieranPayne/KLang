cmake_minimum_required(VERSION 3.10)
project(KLang)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set source directory
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create the executable from all source files
add_executable(test ${SOURCES})
