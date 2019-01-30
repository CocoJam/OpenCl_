cmake_minimum_required(VERSION 3.0)

project(googletest-download NONE)

include(ExternalProject)

ExternalProject_Add(googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           master
  SOURCE_DIR        "C:/Users/james/Desktop/cpp/leetcode/build/3rd_party/google-test/googletest-src"
  BINARY_DIR        "C:/Users/james/Desktop/cpp/leetcode/build/3rd_party/google-test/googletest-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
