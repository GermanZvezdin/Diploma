cmake_minimum_required(VERSION 3.21)
project(Diploma)
set(CMAKE_CXX_STANDARD 20)

include_directories(utils/)
include_directories(utils)

file(GLOB_RECURSE utils_source "utils/*.c*")
file(GLOB_RECURSE utils_include "utils/*.h*")
file(GLOB_RECURSE src "src/*.c*")

add_executable(${PROJECT_NAME} ${utils_include} ${utils_source} ${src})
