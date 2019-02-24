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
#include "Def.h"
#include "CL\cl.h"
#include "CL\cl_ext.h"
// Macros for OpenCL versions
#define OPENCL_VERSION_1_2  1.2f
#define OPENCL_VERSION_2_0  2.0f
class KernelFactory: public OCL{
    private:
        OCL ocl;
    public:
        KernelFactory(const char* preferred=NULL);
        cl_kernel kernel(const char* fileName, cl_context context=NULL, const char* option="-I");
};
#endif