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
    cl_int ciErrNum = CL_SUCCESS;
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
    cl::Context context_();
    cl::Context context_(std::vector<cl::Device> devices);
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

    ~Utils();
};
#endif