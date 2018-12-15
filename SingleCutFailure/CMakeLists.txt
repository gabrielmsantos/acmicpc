cmake_minimum_required(VERSION 2.8)
project(SingleCut)
file(GLOB_RECURSE SOURCES "src/*.cpp")

#Adding pthread to linking flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(single_cut.bin ${SOURCES})

