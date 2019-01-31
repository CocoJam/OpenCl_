#include "Utils.hpp"

Utils::Utils(){
    getPlateform();
    for (cl::Platform& i : this->all_platforms) {
       GetDevice(i);
    }
    setDefaultDevice();
}

Utils::Utils(bool gpu){
    this->isGPU = true;
    getPlateform();
    for (cl::Platform& i : this->all_platforms) {
        if(gpu){
            GetDevice(i, CL_DEVICE_TYPE_GPU);
        }else{
            GetDevice(i);
        }
    }
    setDefaultDevice();
}

Utils::Utils(std::string prefix_platform){
    std::cout<< "prefix platform: "<< prefix_platform<<std::endl;
    getPlateform();
    for (cl::Platform& i : this->all_platforms) {
        std::size_t found =  i.getInfo<CL_PLATFORM_NAME>().find(prefix_platform);
        if (found!=std::string::npos){
            GetDevice(i);
        }
    }
    setDefaultDevice();
}

Utils::~Utils()
{   
     cl_int ciErrNum =  clReleaseContext(this->context());
    if(ciErrNum == CL_SUCCESS){
        std::cout<< "Context released"<<std::endl;
    }
    else{
        std::cout<< "Context not released"<<std::endl;
    }
    std::cout<< "Destroy opencl Object"<<std::endl;
}

void Utils::default_device_(std::string str){
    for(const cl::Device& i:this->all_devices) {
        std::string device_name = i.getInfo<CL_DEVICE_NAME>();
        std::cout<< "Detected device: "<<i.getInfo<CL_DEVICE_NAME>()<<std::endl;
        std::string::const_iterator it;
        it = search(device_name.begin(), device_name.end(), str.begin(), str.end());
        if(str.size()>=1){
            std::size_t found = device_name.find(str);
             if (found!=std::string::npos){
            this->default_device = i;
            }
        }
    }
    this->default_device = this->default_device.getInfo<CL_DEVICE_NAME>() == "" ? this->all_devices[0]: this->default_device; 
    std::cout<< "Using device: "<< this->default_device.getInfo<CL_DEVICE_NAME>() << " as default device"<<std::endl;

}

void Utils::setDefaultDevice(std::string str){
    default_device_(str);
    return;
}

void Utils::setDefaultDevice(){
    std::string str = "GeForce";
    default_device_(str);
    return;
}

void Utils::setDefaultDevice(cl::Device& default_device){
    this->default_device = default_device;
    return;
}

void Utils::getPlateform(){

    cl::Platform::get(&this->all_platforms);
    
    return;
}

void Utils::GetDevice_(cl::Platform& platform, int cl_type){
    cl::Platform default_platform= platform;
    std::cout << "Using platform: "<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";
    std::vector<cl::Device> all_devices;
    
    std::cout<< CL_DEVICE_TYPE_ALL<<std::endl;
    cl_type = cl_type == 0? CL_DEVICE_TYPE_ALL: cl_type;
    default_platform.getDevices(cl_type, &all_devices);
    this->all_devices.resize(this->all_devices.size()+all_devices.size()); 
    std::copy_backward(all_devices.begin(), all_devices.end(), this->all_devices.end() );
    return;
}

void Utils::GetDevice(cl::Platform& platform){
        GetDevice_(platform, 0);
        return;
}

void Utils::GetDevice(cl::Platform& platform, int cl_type){
        GetDevice_(platform, cl_type);
        return;
}

std::vector<cl::Device> Utils::getAllDevices(){
    return this->all_devices;
}

void Utils::DeviceInfo(){
    this->DeviceInfo(this->default_device);
    return;
}


void Utils::DeviceInfo(cl::Device device){
    std::cout<< "CL_DEVICE_TYPE: " << device.getInfo<CL_DEVICE_NAME>() << std::endl;
    std::cout<< "CL_DEVICE_MAX_COMPUTE_UNITS: " <<  device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>() << std::endl;
    std::cout<< "CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS: " <<  device.getInfo<CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS>() << std::endl;
    std::cout<< "CL_DEVICE_MAX_WORK_GROUP_SIZE: " <<  device.getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>() << std::endl;
    std::vector<size_t> d = device.getInfo<CL_DEVICE_MAX_WORK_ITEM_SIZES>(); 
    std::cout << "\t\tMax Work-group Dims: (";
        for (std::vector<size_t>::iterator st = d.begin(); st != d.end(); st++)
          std::cout << *st << " ";
       std::cout << "\x08)" << std::endl;
    size_t size;
    size = device.getInfo<CL_DEVICE_LOCAL_MEM_SIZE>();
    std::cout << "\t\tLocal Memory Size: " << size/1024 << " KB" << std::endl;
    size = device.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>();
    std::cout << "\t\tGlobal Memory Size: " << size/(1024*1024) << " MB" << std::endl;
    size = device.getInfo<CL_DEVICE_MAX_MEM_ALLOC_SIZE>();
    std::cout << "\t\tMax Alloc Size: " << size/(1024*1024) << " MB" << std::endl;
    return;
    }

cl::Context Utils::context_(){
    return this->context_<cl::Device>(this->default_device);
}

// template<class T>
// cl::Context Utils::context_(T device){
//     cl::Context context(device, NULL, NULL,NULL, &this->ciErrNum);
//       if (ciErrNum != CL_SUCCESS)
//     {
//         std::cout<<"Error: Failed to create OpenCL context!\n"<<std::endl;
//         return ciErrNum;
//     }
//     this->context = context;
//     return context;
// }

cl::Context Utils::context_(std::vector<cl::Device> devices){
    return this->context_<std::vector<cl::Device>>(devices);
}