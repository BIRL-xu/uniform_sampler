cmake_minimum_required(VERSION 3.14)
project(uniformsampler)

set(CMAKE_CXX_STANDARD 14)

find_package(PkgConfig REQUIRED)
pkg_check_modules(YAML_CPP yaml-cpp)
include_directories(
        ${YAML_CPP_INCLUDE_DIRS})

link_directories(${YAML_CPP_LIBRARY_DIRS})

add_executable(uniformsampler main.cpp uniform_sampler.h uniform_sampler.cpp)
target_link_libraries(uniformsampler ${YAML_CPP_LIBRARIES})