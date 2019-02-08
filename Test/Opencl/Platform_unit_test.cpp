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
    std::vector<cl::Platform> vec_platform;
    PlatformTest() {
    }

    virtual ~PlatformTest() {
    }

    virtual void SetUp() {
      cl::Platform::get(&vec_platform);
      platform = new Util::Platform<cl::Device>(vec_platform[0]);
    }

    cl::Platform alterPlatform(int i){
      if(i >= vec_platform.size()){
        return vec_platform[0];
      }
      TearDown();
      platform = new Util::Platform<cl::Device>(vec_platform[i]);
      return  vec_platform[i];
    }

    virtual void TearDown() {
      delete platform;
    }

  };

    TEST_F(PlatformTest, Platform_Constructor) {
        if(platform){
          EXPECT_TRUE(true);
        }else{
          FAIL();
        }
  }

    TEST_F(PlatformTest, Platform_GetDevice_CPU) {
      for(int i=0;i< vec_platform.size(); i++){
        std::vector<cl::Device> all_devices;
        alterPlatform(i).getDevices(CL_DEVICE_TYPE_CPU, &all_devices);
        std::vector<cl::Device> platform_devices = platform->GetDevice();
        for(int j =0; j< all_devices.size(); j++){
          /*
        ******************************
        Test fail:
           all_devices[j].getInfo<0x102B>()
           Which is: "Intel(R) Core(TM) i7-7700HQ CPU @ 2.80GHz\0"
           platform_devices[j].getInfo<0x102B>()
           Which is: "Intel(R) HD Graphics 630\0"
           ********************************
          */
          EXPECT_EQ(all_devices[j].getInfo<CL_DEVICE_NAME>(),platform_devices[j].getInfo<CL_DEVICE_NAME>());
        }
      }
      EXPECT_TRUE(true);
  }

     TEST_F(PlatformTest, Platform_GetDevice_GPU) {
      for(int i=0;i< vec_platform.size(); i++){
        std::vector<cl::Device> all_devices;
        alterPlatform(i).getDevices(CL_DEVICE_TYPE_GPU, &all_devices);
        std::vector<cl::Device> platform_devices = platform->GetDevice();
        for(int j =0; j< all_devices.size(); j++){
          EXPECT_EQ(all_devices[j].getInfo<CL_DEVICE_NAME>(),platform_devices[j].getInfo<CL_DEVICE_NAME>());
        }
      }
  }

TEST_F(PlatformTest, Platform_GetDevice_ALL) {
      for(int i=0;i< vec_platform.size(); i++){
        std::vector<cl::Device> all_devices;
        alterPlatform(i).getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
        std::vector<cl::Device> platform_devices = platform->GetDevice();
        for(int j =0; j< all_devices.size(); j++){
          EXPECT_EQ(all_devices[j].getInfo<CL_DEVICE_NAME>(),platform_devices[j].getInfo<CL_DEVICE_NAME>());
        }
      }
  }
    // TEST_F(PlatformTest, Platform_Set_Context) {
    //   cl::Context con = platform.setContext(platform);
    // }
  //   TEST_F(PlatformTest, Platform_Set_Context) {
    
  // }
}