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
    void default_device_(std::string str);
    void GetDevice_(cl::Platform& plateform, int cl_type);
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
    ~Utils();
};
#endif