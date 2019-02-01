#include<Platform.hpp>

#ifdef __APPLE__
#include <OpenCL/opencl.hpp>
#else
#include <CL/cl.hpp>
#endif
#include <gtest/gtest.h>

namespace {
  class PlatformTest : public ::testing::Test {

  protected:
    Platform *platform;

    Platform() {
    }

    virtual ~Platform() {
    }

    virtual void SetUp() {
      platform = new Platform();
    }

    virtual void TearDown() {
      delete platform;
    }

  };

    TEST_F(PlatformTest, Platform_Constructor) {
   
  }

    TEST_F(PlatformTest, Platform_GetDevice_auto) {
   
  }

    TEST_F(PlatformTest, Platform_GetDevice_CPU) {
   
  }
    TEST_F(PlatformTest, Platform_GetDevice_GPU) {
   
  }
    TEST_F(PlatformTest, Platform_Set_Context) {
    
  }
}