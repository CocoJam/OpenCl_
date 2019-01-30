cmake_minimum_required(VERSION 3.12)
project(General)

file(GLOB_RECURSE HEADER_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE LIB_SOURCE_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Adding cpp for google test

add_library(General ${HEADER_FILES} ${LIB_SOURCE_FILES})


target_include_directories(
    General
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
