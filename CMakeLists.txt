cmake_minimum_required(VERSION 3.0.0)
project(shoptimize)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_RELEASE "-Os")

add_subdirectory(lib/yaml-cpp)

include_directories(lib/yaml-cpp/include)
include_directories(include/)
add_subdirectory(src/)
