#ifndef __KernelFactory__H__
# define __KernelFactory__H__
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <fstream>
#include <OCL.h>
#include <Def.h>
#include <unordered_map>
#include <tuple>
#include "CL\cl.h"
#include "CL\cl_ext.h"
// Macros for OpenCL versions
#define OPENCL_VERSION_1_2  1.2f
#define OPENCL_VERSION_2_0  2.0f
class KernelFactory: public OCL{
    private:
    typedef std::tuple<cl_program, cl_kernel> ProKer;
        OCL ocl;
        std::unordered_map<const char*, ProKer> kernelMap;
    public:
        KernelFactory(const char* preferred=NULL);
        ~KernelFactory();
        cl_kernel kernel(const char* fileName, const char* methodName, cl_context context=NULL, const char* option="-I-cl-kernel-arg-info");
        cl_kernel operator[](const char* methodName);
        cl_uint kernelArgumentCount(cl_kernel ker);
        template<typename T>
        cl_mem memoryBuffer(cl_context context, cl_mem_flags cl_flag,unsigned int size_A, T* h_A_data);
        template<typename T>
        std::tuple<cl_mem,T*> memoryBuffer(cl_context context, cl_mem_flags cl_flag,unsigned int size_A, void (*func)(T*,unsigned int));
        std::vector<cl_kernel_arg_address_qualifier> argQualifier(cl_kernel kernel,cl_uint argNum=0);
};
#endif