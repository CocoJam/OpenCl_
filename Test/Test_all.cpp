#include <Device_unit_test.cpp>
#include <Platform_unit_test.cpp>
#include "gtest/gtest.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}