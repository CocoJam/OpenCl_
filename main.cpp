#include <Utils.hpp>
#include <Platform.hpp>
#include<iostream>
#include  <OCL.h>
#include <vector>
#include <CL/CL.hpp>
int main()
{
  // Utils* u = new Utils("NVIDIA");
  // u->DeviceInfo();
  // u->setContext();
  // delete u;


  std::vector<cl::Platform> vec;
  cl::Platform::get(&vec);
  Util::Platform<cl::Device> plat(vec[0]);
  plat.setContext();
  plat.setQuene();
  // cl::Program p = plat.program_quene("../Kernels/Kernels/add.cl", "add_");
  // std::cout<<p.getInfo()<< std::endl;
  
  std::unordered_map<std::string, std::tuple<cl::Program,cl::Kernel>> programs = plat.getProgramMap();
  for(auto& it:programs){
       std::cout<< it.first << std::endl;
      std::cout<<std::get<0>(it.second).getInfo<CL_PROGRAM_SOURCE>()<< std::endl;

      std::cout<<std::get<1>(it.second).getInfo<CL_KERNEL_NUM_ARGS>()<< std::endl;

  }
  cl::Device* d = new cl::Device(plat.GetDevice()[0]);

  std::cout <<"Device info: " << d->getInfo<CL_DEVICE_VERSION>()<<std::endl;
  delete d;

  // std::cout <<"svm info: " << d->getInfo<CL_DEVICE_SVM_CAPABILITIES>()<<std::endl;
  OCL* ocl = new OCL();
  delete ocl;
  return 0;
}