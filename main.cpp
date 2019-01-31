#include <Utils.hpp>
#include<iostream>
int main()
{
  Utils* u = new Utils("NVIDIA");
  u->DeviceInfo();
  delete u;
  return 0;
}