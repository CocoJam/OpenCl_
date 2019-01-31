#ifndef __Kernels_Utils_H
#define __Kernels_Utils_H

#ifdef __APPLE__
#include <OpenCL/opencl.hpp>
#else
#include <CL/cl.hpp>
#endif
#include <vector>
#include<iostream>
#include <algorithm>
#include <string>
/*
Utility Class to obtain opencl Platforms and devices avaible.

all_platforms = vector of platforms avaible (CPU and GPU).
all_devices = vector of deveices from all/ specfic platforms
default_device = current default go to default in use.
isGPU = bool for specific of using GPU
context = opencl context.
ciErrNUM = cl_int type running error container provided by opencl;
*/
class Utils
{
private:
    std::vector<cl::Platform> all_platforms;
    std::vector<cl::Device> all_devices;
    cl::Device default_device;
    bool isGPU = false;
    std::string prefix_platform;
    cl::Context context; 
    void default_device_(std::string str);
    void GetDevice_(cl::Platform& plateform, int cl_type);
    template<class T>
    cl::Context context_(T device){
    cl::Context context(device, NULL, NULL,NULL, &this->ciErrNum);
      if (ciErrNum != CL_SUCCESS)
    {
        std::cout<<"Error: Failed to create OpenCL context!\n"<<std::endl;
        return ciErrNum;
    }
    this->context = context;
    return context;
    }
    cl_int ciErrNum = CL_SUCCESS;
/*
Utils() default constructor to obtain either all platforms/specific with
prefix (eg NIVIDA);

GetDevice() uses default_device_() to detect devices and set default_device;
consist of preferences either user input or GeForce by default;

setDefaultDevice() is a setter method and prompt at constructor;

getAllDevices() getter method for all_devices vector;

DeviceInfo() cout each or specific device information like memory size,
optimial group/item size and dimensions.

context() generates context for individual platforms, either for each device
or a vector of devices.

*/  
public:
    Utils();
    Utils(bool gpu);
    Utils(std::string prefix_);
    void getPlateform();
    void GetDevice(cl::Platform& plateform);
    void GetDevice(cl::Platform& plateform, int cl_type);
    void setDefaultDevice(cl::Device& default_device);
    void setDefaultDevice(std::string str);
    void setDefaultDevice();
    std::vector<cl::Device> getAllDevices();
    void DeviceInfo();
    void DeviceInfo(cl::Device);
    cl::Context context();
    cl::Context context(std::vector<cl::Device> devices);
    ~Utils();
};
#endif