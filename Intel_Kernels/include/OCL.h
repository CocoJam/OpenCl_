#ifndef __OCL__H_
# define __OCL__H_
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <exception>
#include <fstream>
#include "CL\cl.h"
#include "CL\cl_ext.h"
// Macros for OpenCL versions
#define OPENCL_VERSION_1_2  1.2f
#define OPENCL_VERSION_2_0  2.0f

class OCL{
    protected:
        cl_context       context;           // hold the context handler
        std::vector<cl_device_id>     device;            // hold the selected device handler
        std::vector<cl_command_queue> commandQueue;      // hold the commands-queue handler
        std::vector<cl_program>       program;           // hold the program handler
        std::vector<cl_kernel>        kernel;            // hold the kernel handler
        float            platformVersion;   // hold the OpenCL platform version (default 1.2)
        float            deviceVersion;     // hold the OpenCL device version (default. 1.2)
        float            compilerVersion;   // hold the device OpenCL C version (default. 1.2)
        std::vector<cl_mem> memory_buffer;
        void platform_to_vec(cl_platform_id* platform_vector_id, cl_uint numPlatforms=NULL);
        cl_uint num_of_platform_device(cl_platform_id platform_id, cl_device_type deviceType);
        void device_to_vec( cl_platform_id platform_vector_id, cl_device_id* device_vector_id, cl_device_type deviceType = CL_DEVICE_TYPE_CPU, cl_uint numDevices=NULL);
        template<class T>
        cl_int release_(cl_int(*func) (T), T item, std::string str);
        template<class T>
        void release_(cl_int (*func) (T), std::vector<T> item, std::string str);
        void setup(const char* preferred=NULL);
    public:
        OCL(const char* preferred=NULL);
        ~OCL();
        cl_platform_id preferred_platform(const char* preffered_platform=NULL);
        std::vector<cl_device_id> OCL::platform_device(cl_platform_id platform_id,cl_device_type deviceType=CL_DEVICE_TYPE_CPU, cl_uint numDevices=0);
        cl_context context_with_properties(cl_device_id device_vector_id, cl_platform_id platform_vector_id ,cl_context_properties contextProperties[],cl_uint numdevices=0);
        cl_context context_with_properties(cl_platform_id platform_vector_id ,cl_context_properties contextProperties[]=NULL,cl_device_type deviceType=CL_DEVICE_TYPE_CPU);
        cl_command_queue commandQuene(cl_device_id device_id, cl_context context_id);
        cl_program prgoramWithSource(cl_context context, const char* fileName);
        void programSourceFileReader(const char* fileName, char** source_ptr, size_t* src_size);
        cl_program programBuild(cl_program program, cl_uint numOfDevices, cl_device_id* device_vector_id, const char* option="-I");
        cl_kernel kernelBuild(cl_program program, const char* fileName);
};
#endif