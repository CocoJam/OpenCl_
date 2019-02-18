#include "Platform.hpp"
#include <string>
#include<iostream>
#include <fstream>
#include<unordered_map>
#include <tuple>
// #include <windows.h>
#ifdef _WIN32
#include <direct.h>
#define cwd _getcwd
#define cd _chdir
#else
#include "unistd.h"
#define cwd getcwd
#define cd chdir
#endif

#define MAX_SOURCE_SIZE (0x100000)	
namespace Util{



template<class D>
Platform<D>::Platform(cl::Platform platform){
    this->platform = platform;
    GetDevice(platform);
}

template<class D>
Platform<D>::~Platform()
{   
    release_<cl_context, cl::Context>(clReleaseContext, this->context, "Context");
    release_< cl_command_queue ,cl::CommandQueue>(clReleaseCommandQueue, this->queue, "Queue");
    for(auto& it:ProgramMap){
        release_<cl_kernel , cl::Kernel>(clReleaseKernel, std::get<1>(it.second), it.first);
        release_<cl_program , cl::Program>(clReleaseProgram, std::get<0>(it.second), it.first);
    }
    std::cout<< "Destroy OpenCL::Platform Object"<<std::endl;
}

template<class D>
    template<class T, class T2>
    cl_int Platform<D>::release_(cl_int (*func) (T), T2 item, std::string str){
        auto item_ptr = item();
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

template<class D>
std::vector<D> Platform<D>::GetDevice_(cl::Platform& platform, int cl_type){
    cl::Platform default_platform= platform;
    std::cout << "Using platform: "<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";
    std::vector<D> all_devices;
    std::cout<< CL_DEVICE_TYPE_ALL<<std::endl;
    cl_type = cl_type == 0? CL_DEVICE_TYPE_ALL: cl_type;
    default_platform.getDevices(cl_type, &all_devices); 
    this->all_devices.resize(this->all_devices.size()+all_devices.size()); 
    std::copy_backward(all_devices.begin(), all_devices.end(), this->all_devices.end() );
    return all_devices;
}

template<>
std::vector<Device> Platform<Device>::GetDevice_(cl::Platform& platform, int cl_type){
    cl::Platform default_platform= platform;
    std::cout << "Using platform: "<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";
    std::vector<cl::Device> all_devices;
    std::cout<< CL_DEVICE_TYPE_ALL<<std::endl;
    cl_type = cl_type == 0? CL_DEVICE_TYPE_ALL: cl_type;
    default_platform.getDevices(cl_type, &all_devices); 
    std::vector<Device> all_Utils_devices;
    
    std::vector<Device> ordinals;
    std::transform(all_devices.begin(), all_devices.end(), std::back_inserter(ordinals),
                   [](cl::Device dev) -> Device { 
                       Device util_device(dev);
                       return util_device; });
    this->all_devices = ordinals;
    return ordinals;
}

template<>
std::vector<cl::Device> Platform<cl::Device>::GetDevice_(cl::Platform& platform, int cl_type){
    cl::Platform default_platform= platform;
    std::cout << "Using platform: "<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";
    std::vector<cl::Device> all_devices;
    std::cout<< CL_DEVICE_TYPE_ALL<<std::endl;
    cl_type = cl_type == 0? CL_DEVICE_TYPE_ALL: cl_type;
    default_platform.getDevices(cl_type, &all_devices); 
    this->all_devices.resize(this->all_devices.size()+all_devices.size()); 
    std::copy_backward(all_devices.begin(), all_devices.end(), this->all_devices.end() );
    return all_devices;
}

template<class D>
std::vector<D> Platform<D>::GetDevice(){
    if(&this->all_devices ==NULL){
        GetDevice_(this->platform, 0);
    }
        return this->all_devices;
}

template<class D>
std::vector<D> Platform<D>::GetDevice(cl::Platform& platform){
        return GetDevice_(platform, 0);
}

template<class D>
std::vector<D> Platform<D>::GetDevice(cl::Platform& platform, int cl_type){
        return GetDevice_(platform, cl_type);
}

template<class D>
cl::Context Platform<D>::setContext(D device){
    return this->context_<D>(device);
}

template<class D>
cl::Context Platform<D>::setContext(){
    if(this->all_devices.size() < 1){
        GetDevice_(this->platform, 0);
    }
    /*
    int i = 
    while(&this->all_Devices.size() <1){
        GetDevice_(this->platform, i);
    }
    */
    return this->context_<std::vector<D>>(all_devices);
}

// template<class D>
// cl::Context Platform<D>::setContext(std::vector<D> devices){
//     return this->context_<std::vector<D>>(devices);
// }

template<class D>
    template<class T>
    cl::Context Platform<D>::context_(T device){
        T dev = device;
        cl_int err = CL_SUCCESS;
        cl_int* err_ptr = &err;
        cl::Context context(dev, NULL, NULL,NULL,err_ptr);
            if (ciErrNum != err){
                std::cout<<"Error: Failed to create OpenCL context!\n"<<std::endl;
                return ciErrNum;
            }
        this->context = context;
        return context;
    }

template<class D>
cl::CommandQueue Platform<D>::setQuene(){
    if(&context == NULL){
        this->setContext();
    }

    cl_int err = CL_SUCCESS;
    cl_int* err_ptr = &err;

    cl::CommandQueue q(this->context,0, err_ptr);
         if (ciErrNum != err){
                std::cout<<"Error: Failed to create OpenCL Command Queue!\n"<<std::endl;
                return ciErrNum;
            }
        this->queue = q;
        return q;
}
//


template<class D>
// template<bool buildKernel=true>
cl::Program Platform<D>::program_quene(const char * filename,bool buildKernel){
    return this->program_quene(filename,filename, buildKernel);
}

// template<class D>
// // template<bool buildKernel=true>
// cl::Program Platform<D>::program_quene(std::string filename, std::string methodname,bool buildKernel){
//     return this->program_quene(filename.c_str(), methodname.c_str(),buildKernel);
// }


//
// template<class D>
// cl_program Platform<D>::program_quene(char[] filename){
//     char* file_name_ptr = &filename;
//     return program_quene(file_name_ptr);
// }

template<class D>
cl::Program Platform<D>::program_quene(const char * fileName, const char * methodName, bool buildKernel){
    
    std::ifstream file(fileName);
    std::string str = "";
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            str+= line.c_str();
        }
        file.close();
    }else{
        char buf[4096];
        std::cout  << "CWD: " << cwd(buf, sizeof buf) << std::endl;
        std::cout<< fileName << " is not found."<<std::endl;
    }
    cl::Program::Sources sources;
    sources.push_back({str.c_str(),str.length()});
    if(&this->context == NULL){
        setContext();
    }
    cl_int err = CL_SUCCESS;
    cl_int* err_ptr = &err;
    // cl::Program program(this->context,sources, err_ptr);
    cl::Program program(this->context,sources);
    if(program.build(this->all_devices)!=CL_SUCCESS){
        std::cout<<" Error building: "<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(this->all_devices[0])<<"\n";
        exit(1);
    }
    cl::Kernel kernel;
    if(buildKernel){
        // const char * c = methodName.c_str();
        kernel= cl::Kernel(program,methodName);
    }else{
        kernel= cl::Kernel();
    }
    this->ProgramMap[methodName]=std::make_tuple(program, kernel);        
    std::cout<< "Quened: "<< methodName<<std::endl;
    return program;
}

template<class D>
std::unordered_map<std::string, std::tuple<cl::Program,cl::Kernel>> Platform<D>::getProgramMap(){
    if(&ProgramMap == NULL){
           throw std::invalid_argument("Platform doesn't have Program Map");
    }else{
        return this->ProgramMap;
    }
}



template class Platform<cl::Device>;
// template class Platform<Device>;
}
