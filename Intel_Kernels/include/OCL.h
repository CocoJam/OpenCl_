#ifndef __OCL__H_
# define __OCL__H_
#include <string>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include "CL\cl.h"
#include "CL\cl_ext.h"
// Macros for OpenCL versions
#define OPENCL_VERSION_1_2  1.2f
#define OPENCL_VERSION_2_0  2.0f

class OCL{
    private:
        cl_context       context;           // hold the context handler
        std::vector<cl_device_id>     device;            // hold the selected device handler
        cl_command_queue commandQueue;      // hold the commands-queue handler
        std::vector<cl_program>       program;           // hold the program handler
        std::vector<cl_kernel>        kernel;            // hold the kernel handler
        float            platformVersion;   // hold the OpenCL platform version (default 1.2)
        float            deviceVersion;     // hold the OpenCL device version (default. 1.2)
        float            compilerVersion;   // hold the device OpenCL C version (default. 1.2)
        std::vector<cl_mem> memory_buffer;
        template<class T>
        cl_int release_(cl_int(*func) (T), T item, std::string str);
    public:
        OCL();
        ~OCL();
};
#endif