cmake_minimum_required(VERSION 3.12)
project(unit_test)

enable_testing()

file(GLOB_RECURSE unit_general_test_files ${CMAKE_CURRENT_SOURCE_DIR}/General/*.cpp)
file(GLOB_RECURSE unit_data_structure_test_files ${CMAKE_CURRENT_SOURCE_DIR}/Data_structure/*.cpp)

file(GLOB_RECURSE unit_OpenCL_test_files ${CMAKE_CURRENT_SOURCE_DIR}/Opencl/*.cpp)

function(test_generation file_item file_name type_of_library GTEST GMAIN)
    
message(STATUS ${file_item})
get_filename_component(MYFILE_WITHOUT_EXT ${file_item} NAME_WE)
include(GoogleTest)

message(STATUS ${MYFILE_WITHOUT_EXT})

add_executable(${MYFILE_WITHOUT_EXT} ${file_item})

target_link_libraries(
    ${MYFILE_WITHOUT_EXT} 
    ${type_of_library}
    ${GTEST}
    ${GMAIN}
)

# gtest_add_tests(TARGET ${MYFILE_WITHOUT_EXT} TEST_PREFIX old:)
# gtest_discover_tests(${MYFILE_WITHOUT_EXT} TEST_PREFIX new:)
add_test(AllTest ${MYFILE_WITHOUT_EXT})

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

