#include <Utils.hpp>
#include<iostream>
int main()
{
  Utils* u = new Utils("NVIDIA");
  u->DeviceInfo();
  u->setContext();
  delete u;
  return 0;
}