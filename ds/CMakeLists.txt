cmake_minimum_required(VERSION 3.12)
project(data_structure)

file(GLOB_RECURSE HEADER_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE LIB_SOURCE_FILES  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(data_structure ${HEADER_FILES} ${LIB_SOURCE_FILES})

target_include_directories(
    data_structure
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
