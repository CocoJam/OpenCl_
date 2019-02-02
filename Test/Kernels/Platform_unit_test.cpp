#include <Platform.hpp>

#ifdef __APPLE__
#include <OpenCL/opencl.hpp>
#else
#include <CL/cl.hpp>
#endif
#include <gtest/gtest.h>

namespace {
  class PlatformTest : public ::testing::Test {

  protected:
    Util::Platform<cl::Device> *platform;
    std::vector<cl::Device> vec;
    PlatformTest() {
    }

    virtual ~PlatformTest() {
    }

    virtual void SetUp() {
      cl::Platform::get(&vec);
      platform = new Util::Platform<cl::Device>(vec[0]);
    }

    virtual void TearDown() {
      delete platform;
    }

  };

    TEST_F(PlatformTest, Platform_Constructor) {
        if(platform){
          EXPECT_TRUE(true);
          return;
        }
        FAIL();
  }

    TEST_F(PlatformTest, Platform_GetDevice_auto) {
      //  vec[0].getInfo<CL_PLATFORM_NAME>()
      std::vector<cl::Device> all_devices;
      
      vec[0].getAllDevices()
      platform->GetDevice()[0]

  }

  //   TEST_F(PlatformTest, Platform_GetDevice_CPU) {
   
  // }
  //   TEST_F(PlatformTest, Platform_GetDevice_GPU) {
   
  // }
  //   TEST_F(PlatformTest, Platform_Set_Context) {
    
  // }
}