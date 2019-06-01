cmake_minimum_required(VERSION 3.0)
project(tstflat)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(${PROJECT_SOURCE_DIR}/schema)

add_executable(writer writer.cpp)

add_executable(reader reader.cpp)

add_dependencies(reader schema_headers)
add_dependencies(writer schema_headers)

include_directories("\\Users\\Daniel\\flatbuffers\\include")
include_directories(include)
