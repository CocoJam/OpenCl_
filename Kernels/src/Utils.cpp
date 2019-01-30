#include "Utils.hpp"

Utils::Utils(){
    std::cout<< "Init opencl"<<std::endl;
    getPlateform();
    for (cl::Platform& i : this->all_platforms) {
       GetDevice(i);
    }
    setDefaultDevice();
}

Utils::~Utils()
{
    std::cout<< "destroy opencl"<<std::endl;
}

void Utils::setDefaultDevice(){
    std::string str = "NVIDIA";
    for(const cl::Device& i:this->all_devices) {

        std::string device_name = i.getInfo<CL_DEVICE_NAME>();

        std::cout<< "Detected device: "<<i.getInfo<CL_DEVICE_NAME>()<<std::endl;
        std::string::const_iterator it;
        it = search(device_name.begin(), device_name.end(), str.begin(), str.end());
        if (it != device_name.end()){
            this->default_device = i;
        }
    }
    std::cout<< "Using device: "<< this->default_device.getInfo<CL_DEVICE_NAME>() << " as default device"<<std::endl;
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

void Utils::GetDevice(cl::Platform& plateform){
        cl::Platform default_platform= plateform;
        std::cout << "Using platform: "<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";
        std::vector<cl::Device> all_devices;
        default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
        this->all_devices.resize(this->all_devices.size()+all_devices.size()); 
        std::copy_backward(all_devices.begin(), all_devices.end(), this->all_devices.end() );
        return;
}