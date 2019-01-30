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
public:
    Utils();
    void getPlateform();
    void GetDevice(cl::Platform& plateform);
    void setDefaultDevice(cl::Device& default_device);
    void setDefaultDevice();
    ~Utils();
};
#endif