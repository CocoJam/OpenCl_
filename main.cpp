#include <Utils.hpp>
#include <Platform.hpp>
#include<iostream>

#include <vector>
#include <CL/cl.hpp>
int main()
{
  // Utils* u = new Utils("NVIDIA");
  // u->DeviceInfo();
  // u->setContext();
  // delete u;


  std::vector<cl::Platform> vec;
  cl::Platform::get(&vec);
  Util::Platform<cl::Device> plat(vec[0]);
 
  cl::Device* d = new cl::Device(plat.GetDevice()[0]);
  std::cout <<"Device info: " << d->getInfo<CL_DEVICE_NAME>()<<std::endl;
  return 0;
}