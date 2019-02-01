#ifndef __Kernels_Utils_PlatForm_H_
#define __Kernels_Utils_PlatForm_H_

#ifdef __APPLE__
#include <OpenCL/opencl.hpp>
#else
#include <CL/cl.hpp>
#endif
#include <iostream>
#include <algorithm>
#include "Device.hpp"
namespace Util
{
    template<class D>
    class Platform
    {
    private:
        cl::Platform platform;
        std::vector<D> all_devices;
        cl::Context context;
        cl_int ciErrNum = CL_SUCCESS;
        std::vector<D> GetDevice_(cl::Platform& plateform, int cl_type);
        template<class T>
        cl::Context context_(T device);
    public:
        Platform(cl::Platform platform);
        ~Platform();
        std::vector<D> GetDevice();        
        std::vector<D> GetDevice(cl::Platform& plateform);
        std::vector<D> GetDevice(cl::Platform& plateform, int cl_type);
        cl::Context setContext(D device);
        cl::Context setContext(std::vector<D> device);
    };


} // Utils
#endif