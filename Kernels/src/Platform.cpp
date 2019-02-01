#include "Platform.hpp"


namespace Util{



template<class D>
Platform<D>::Platform(cl::Platform platform){
    this->platform = platform;
    GetDevice(platform);
}

template<class D>
Platform<D>::~Platform()
{   
     cl_int ciErrNum =  clReleaseContext(this->context());
    if(ciErrNum == CL_SUCCESS){
        std::cout<< "Context released"<<std::endl;
    }
    else if(&this->context == NULL){
            std::cout<< "Context not released"<<std::endl;
    }
    else{
            std::cout<< "Context not released"<<std::endl;        
        }
    std::cout<< "Destroy OpenCL::Platform Object"<<std::endl;
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

// template<class D>
// cl::Context Platform<D>::setContext(std::vector<D> devices){
//     return this->context_<std::vector<D>>(devices);
// }

template<class D>
    template<class T>
    cl::Context Platform<D>::context_(T device){
        T dev = device;
        cl::Context context(dev, NULL, NULL,NULL, NULL);
            if (ciErrNum != CL_SUCCESS){
                std::cout<<"Error: Failed to create OpenCL context!\n"<<std::endl;
                return ciErrNum;
            }
        this->context = context;
        return context;
    }

template class Platform<cl::Device>;
template class Platform<Device>;
}
