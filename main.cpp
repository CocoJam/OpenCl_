#include <Utils.hpp>
#include <Platform.hpp>
#include<iostream>
#include <string>
#include <OCL.h>
#include <Def.h>
#include <OCL_Kernel_factory.h>
#include <vector>
#include <CL/CL.hpp>
int main()
{
  KernelFactory* k = new KernelFactory();
  cl_kernel ker = k->kernel("../../add.cl","add");
  std::vector<cl_kernel_arg_address_qualifier> vec = k->argQualifier(ker);
  for(auto i:vec){
    std::cout<< i<< "\n";
  }
  delete k;
  return 0;
}