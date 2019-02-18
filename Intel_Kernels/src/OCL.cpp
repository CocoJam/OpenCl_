#include "OCL.h"

OCL::OCL(): 
        context(NULL),
        // device(std::vector<cl_device_id>),
        commandQueue(NULL),
        // program(std::vector<cl_program>),
        // kernel(std::vector<cl_kernel>),
        platformVersion(OPENCL_VERSION_1_2),
        deviceVersion(OPENCL_VERSION_1_2),
        compilerVersion(OPENCL_VERSION_1_2){};
        // memory_buffer(std::vector<cl_mem>)
OCL::~OCL(){
    release_<cl_context>(clReleaseContext, this->context, "Context");
    release_<cl_command_queue>(clReleaseCommandQueue, this->commandQueue, "Queue");
}

template<class T>
cl_int OCL::release_(cl_int (*func) (T), T item, std::string str){
    // std::string s = typeid(item).name();
    // std::string vector_name = "St6vector";
    // std::string::const_iterator it;
    //   it = search(vector_name.begin(), vector_name.end(), s.begin(), s.end());
    //     if(s.size()>=1){
    //         std::size_t found = device_name.find(str);
    //          if (found!=std::string::npos){
    //                for(auto& i:item){
    //                 release_(func, i, str);
    //             }
    //         }
    //     }
    auto item_ptr = item;
    if(&item == NULL){
        std::cout<< str << " is NULL"<< std::endl;
        return CL_INVALID_EVENT;
    }
    cl_int ciErrNum = func(item_ptr);
  if(ciErrNum == CL_SUCCESS){
        std::cout<< str <<" released"<<std::endl;
    }
    else if(&item == NULL){
            std::cout<< str <<" not released, due to Null of "<< str<<std::endl;
    }
    else{
            std::cout<< str <<" not released"<<std::endl;        
    }
    return ciErrNum;
}
