#ifndef __OCL__H_
# define __OCL__H_
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <fstream>
#include <OCL.h>
#include "CL\cl.h"
#include "CL\cl_ext.h"
// Macros for OpenCL versions
#define OPENCL_VERSION_1_2  1.2f
#define OPENCL_VERSION_2_0  2.0f
class KernelFactory:public OCL{
    private:
        
    public:
        KernelFactory(const char* preferred=NULL);
};
#endif