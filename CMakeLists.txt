cmake_minimum_required(VERSION 3.0.0)
project(shoptimize)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-Os")

include_directories(lib/yaml-cpp/include)
include_directories(include/)

add_subdirectory(lib/yaml-cpp)

set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Werror")

add_subdirectory(src/)
