cmake_minimum_required(VERSION 3.5)
set (CMAKE_CXX_STANDARD 17)
project(project_GPU)

# Adding data_structure librarys
# add_subdirectory(ds)
# add_subdirectory(General)
add_subdirectory(Kernels)
add_executable(main main.cpp)
# FIND_PACKAGE(OpenCL 2.0 REQUIRED)
include_directories(${INTELOCLSDKROOT}/include)

file(GLOB_RECURSE HEADER_FILES_  ${CMAKE_CURRENT_SOURCE_DIR}/CL_2_0/CL)
INCLUDE_DIRECTORIES(${OPENCL_INCLUDE_DIR} ${HEADER_FILES_})
link_directories(${INTELOCLSDKROOT}/lib/x86)

# set(Boost_USE_MULTITHREADED      ON)
# set(Boost_INCLUDE_DIR C:/Users/james/Desktop/boost_1_69_0)
# set(Boost_LIBRARY_DIR C:/Users/james/Desktop/boost_1_69_0/stage/lib)

# set(Boost_USE_STATIC_LIBS OFF)
# set(Boost_USE_MULTITHREADED ON)
# set(Boost_USE_STATIC_RUNTIME OFF)
# find_package(Boost 1.50 REQUIRED)
# include_directories( ${Boost_INCLUDE_DIRS} )
# message(STATUS "Boost version: ${Boost_VERSION}")

# if(NOT TARGET Boost::filesystem)
#     add_library(Boost::filesystem IMPORTED INTERFACE)
#     set_property(TARGET Boost::filesystem PROPERTY
#         INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
#     set_property(TARGET Boost::filesystem PROPERTY
#         INTERFACE_LINK_LIBRARIES ${Boost_LIBRARIES})
# endif()

# target_link_libraries(MyExeOrLibrary PUBLIC Boost::filesystem)

target_link_libraries(
    main
    PRIVATE
    # data_structure
    kernels
    # ${Boost_LIBRARIES}
    # Boost::filesystem
    # OpenCL::OpenCL
)

# add_dependencies(main OpenCL::OpenCL)
# add_dependencies(main data_structure)
add_dependencies(main kernels)
# add_subdirectory(3rd_party/google-test)
# add_subdirectory(Test)

