#include <string>
#include "Utils.hpp"
#ifdef __APPLE__
#include <OpenCL/opencl.hpp>
#else
#include <CL/cl.hpp>
#endif
#include <gtest/gtest.h>

namespace {
  class UtilsTest : public ::testing::Test {

  protected:
    Utils *utils;

    UtilsTest() {
    }

    virtual ~UtilsTest() {
    }

    virtual void SetUp() {
      utils = new Utils();
    }
    
    void SetUp(std::string prefix_) {
      delete utils;
      utils = new Utils(prefix_);
    }

    virtual void TearDown() {
      delete utils;
    }

  };

  TEST_F(UtilsTest, Utils_List_Of_Platform) {
    std::vector<cl::Platform> all_platforms;
    cl::Platform::get(&all_platforms);
    std::vector<cl::Platform> all_platforms_test = utils->getPlateform();
    EXPECT_EQ(all_platforms.size(),all_platforms_test.size());
    for(int i= 0; i< all_platforms.size() ; i++){
           EXPECT_EQ(all_platforms[i].getInfo<CL_PLATFORM_NAME>(), all_platforms_test[i].getInfo<CL_PLATFORM_NAME>() );
    }
  }

    TEST_F(UtilsTest, Utils_List_Of_Device) {
        std::vector<cl::Platform> all_platforms_test = utils->getPlateform();
        for(int i=0;i<all_platforms_test.size();i++){
         std::vector<cl::Device> dev_cpu =  utils->GetDevice( all_platforms_test[i],CL_DEVICE_TYPE_CPU);
        std::vector<cl::Device> dev_gpu =  utils->GetDevice( all_platforms_test[i],CL_DEVICE_TYPE_GPU);
         for(cl::Device j: dev_cpu){
            EXPECT_EQ(j.getInfo<CL_DEVICE_TYPE>(),CL_DEVICE_TYPE_CPU);
         };
         for(cl::Device j: dev_gpu){
            EXPECT_EQ(j.getInfo<CL_DEVICE_TYPE>(),CL_DEVICE_TYPE_GPU);
         };
    }
  }

    TEST_F(UtilsTest, Utils_constructor_with_prefix) {
        SetUp("Intel(R)");
        for(cl::Platform i : utils->getPlateform()){
            std::size_t found =  i.getInfo<CL_PLATFORM_NAME>().find("Intel(R)");
            if (found != std::string::npos){
              EXPECT_TRUE(true);
              return;
            }
        }
        FAIL();
    }

    TEST_F(UtilsTest, Utils_set_defaultDevice){
      utils->setDefaultDevice("GeForce");
      cl::Device dev = utils->getDefaultDevice();
       std::size_t found =  dev.getInfo<CL_DEVICE_NAME>().find("GeForce");
            if (found != std::string::npos){
              EXPECT_TRUE(true);
              return;
            }
      FAIL();
    }
}