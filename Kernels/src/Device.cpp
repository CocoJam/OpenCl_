#include "Device.hpp"

Util::Device::Device(cl::Platform platform, cl::Device device):cl::Device(device), Parent_platform(&platform){
    this->DeviceID = device();

}

Util::Device::Device(cl::Device device) :cl::Device(device){
    this->DeviceID = device();

}

template<typename T>
auto Util::Device::Info(){
    return this->getInfo<T>();
}

Util::Device::Device():cl::Device(){}

Util::Device::~Device(){}