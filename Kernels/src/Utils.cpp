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