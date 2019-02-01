#ifndef __Kernels_Utils_Device_H_
#define __Kernels_Utils_Device_H_

#ifdef __APPLE__
#include <OpenCL/opencl.hpp>
#else
#include <CL/cl.hpp>
#endif

namespace Util{
    class Device: public cl::Device
    {
    private:
        cl::Device device;
        cl_device_id DeviceID;
        cl::Platform* Parent_platform;

    public:
        Device();
        Device(cl::Platform platform, cl::Device device);
        Device(cl::Device device);
        ~Device();
        template<typename T>
        auto Info();
    };
    
}
#endif