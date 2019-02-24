#include <Utils.hpp>
#include <Platform.hpp>
#include<iostream>
#include  <OCL.h>
#include <OCL_Kernel_factory.h>
#include <vector>
#include <CL/CL.hpp>
int main()
{
  OCL* ocl = new OCL();
  delete ocl;

  KernelFactory* k = new KernelFactory();
  k->kernel("Kernel/re.cl");
  delete k;
  return 0;
}