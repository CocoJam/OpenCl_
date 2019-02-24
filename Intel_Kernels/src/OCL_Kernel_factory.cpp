#include "OCL_Kernel_factory.h"
KernelFactory::KernelFactory(const char* preferred): OCL(preferred){};
cl_kernel KernelFactory::kernel(const char* fileName, cl_context context, const char* option){
    if(context == NULL){
        context = this->context;
    }
     cl_program program =NULL;
    try{
        cl_program program = prgoramWithSource(context, fileName);
    }
    catch_block;
    program = programBuild(program, device.size(),&device[0],option);
    cl_kernel kernel = kernelBuild(program, fileName);
    return kernel;
}
