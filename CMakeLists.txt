cmake_minimum_required(VERSION 3.0)
project(tstflat)

set(CMAKE_CXX_STANDARD 14)

add_executable(writer writer.cpp)

add_executable(reader reader.cpp)

include_directories("\\Users\\Daniel\\flatbuffers\\include")
