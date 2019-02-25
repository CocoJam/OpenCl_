#include "OCL_Kernel_factory.h"
// #include
KernelFactory::KernelFactory(const char* preferred): OCL(preferred){};
KernelFactory::~KernelFactory(){
    for(auto& it:kernelMap){
        release_<cl_kernel>(clReleaseKernel, std::get<1>(it.second), it.first);
        release_<cl_program>(clReleaseProgram, std::get<0>(it.second), it.first);
    }
    // OCL::~OCL();
}
cl_kernel KernelFactory::kernel(const char* fileName, const char* methodName, cl_context context, const char* option){
    cl_program program =NULL;
    cl_kernel kernel =NULL;
    try{
        program = prgoramWithSource(this->context, fileName);
        program = programBuild(program, this->device.size(),&this->device[0],option);
        kernel = kernelBuild(program, methodName);
    }
    catch_block(this);
    ProKer pk = std::make_tuple(program,kernel);
    kernelMap[methodName] = pk;
    return kernel;
}
cl_kernel KernelFactory::operator[](const char* methodName){
    return std::get<1>(kernelMap[methodName]);
}
template<typename T>
cl_mem KernelFactory::memoryBuffer(cl_context context, cl_mem_flags cl_flag,unsigned int size_A, T* h_A_data){
    cl_int err = CL_SUCCESS;
    unsigned int mem_size_A = sizeof(T) * size_A;
    T* h_A_data = (T*)malloc(mem_size_A);
    func(h_A_data,size_A);
    cl_mem h_A = clCreateBuffer(cxGPUContext,cl_flag, mem_size_A, h_A_data, &err);
    if(err!=CL_SUCCESS){
        throw  std::invalid_argument(throw_error(OpenCLError(err)));
    }
    return h_A;
}
template<typename T>
std::tuple<cl_mem,T*> KernelFactory::memoryBuffer(cl_context context, cl_mem_flags cl_flag,unsigned int size_A, void (*func)(T*,unsigned int)){
    cl_int err = CL_SUCCESS;
    unsigned int mem_size_A = sizeof(T) * size_A;
    T* h_A_data = (T*)malloc(mem_size_A);
    func(h_A_data,size_A);
    cl_mem h_A = clCreateBuffer(cxGPUContext,cl_flag, mem_size_A, h_A_data, &err);
    if(err!=CL_SUCCESS){
        throw  std::invalid_argument(throw_error(OpenCLError(err)));
    }
    return std::make_pair(h_A, h_A_data);;
}
cl_uint KernelFactory::kernelArgumentCount(cl_kernel ker){
  std::vector<cl_uint> args;
  getInfoVec(clGetKernelInfo,ker,CL_KERNEL_NUM_ARGS,args,cl_uint);
  std::string str(args.begin(),args.end());
  return args[0];
}
std::vector<cl_kernel_arg_address_qualifier> KernelFactory::argQualifier(cl_kernel kernel,cl_uint argNum){
    if(argNum==0){
        argNum = this->kernelArgumentCount(kernel);
    }
    std::vector<cl_kernel_arg_address_qualifier> vec(argNum);
    for(int i=0;i<argNum;i++){
        getArgVec(clGetKernelArgInfo,kernel,i,CL_KERNEL_ARG_ADDRESS_QUALIFIER, vec);
    }
    return vec;
}
// void KernelFactory::copy(cl_command_queue queue, ){

// }