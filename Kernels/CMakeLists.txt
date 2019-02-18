cmake_minimum_required(VERSION 3.12)
project(kernels)
set (CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE HEADER_FILES_  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE LIB_SOURCE_FILES_  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(kernels ${HEADER_FILES_} ${LIB_SOURCE_FILES_})
FIND_PACKAGE(OpenCL REQUIRED)
INCLUDE_DIRECTORIES(${OPENCL_INCLUDE_DIR})
link_directories(${OpenCL_LIBRARY})

target_link_libraries(
    kernels
    OpenCL::OpenCL
)

target_include_directories(
    kernels
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
