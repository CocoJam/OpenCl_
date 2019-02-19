cmake_minimum_required(VERSION 3.12)
project(unit_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W1")
include(ExternalProject)
ExternalProject_Add(gtest
  URL https://github.com/google/googletest/archive/release-1.8.0.zip
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
  INSTALL_COMMAND ""
)
ExternalProject_Get_Property(gtest source_dir binary_dir)
include_directories(${source_dir}/include)
enable_testing()

# FIND_PACKAGE(OpenCL REQUIRED)
# INCLUDE_DIRECTORIES(${OPENCL_INCLUDE_DIR})
# link_directories(${OpenCL_LIBRARY})

file(GLOB_RECURSE unit_general_test_files ${CMAKE_CURRENT_SOURCE_DIR}/General/*.cpp)
file(GLOB_RECURSE unit_data_structure_test_files ${CMAKE_CURRENT_SOURCE_DIR}/Data_structure/*.cpp)

file(GLOB_RECURSE unit_OpenCL_test_files ${CMAKE_CURRENT_SOURCE_DIR}/Opencl/*.cpp)

function(test_generation file_item file_name type_of_library GTEST GMAIN)
    
message(STATUS ${file_item})
get_filename_component(MYFILE_WITHOUT_EXT ${file_item} NAME_WE)
# include(GoogleTest)

message(STATUS ${MYFILE_WITHOUT_EXT})

add_executable(${MYFILE_WITHOUT_EXT} ${file_item})
add_dependencies(${MYFILE_WITHOUT_EXT} gtest)
target_link_libraries(
    ${MYFILE_WITHOUT_EXT} 
    ${type_of_library}
    ${binary_dir}/libgtest.a
    ${binary_dir}/libgtest_main.a
    # OpenCL::OpenCL
)
add_test(NAME     ${MYFILE_WITHOUT_EXT}  
         COMMAND  ${MYFILE_WITHOUT_EXT} )

endfunction(test_generation)

foreach(item ${unit_general_test_files})
test_generation(${item} ${item} General  GTest::GTest  GTest::Main)
endforeach()

foreach(item ${unit_data_structure_test_files})
test_generation(${item} ${item} data_structure  GTest::GTest  GTest::Main)
endforeach()

foreach(item ${unit_OpenCL_test_files})
test_generation(${item} ${item} kernels  GTest::GTest  GTest::Main)
endforeach()

