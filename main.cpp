#include <Utils.hpp>
#include<iostream>
int main()
{
  Utils* u = new Utils("NVIDIA");
  u->DeviceInfo();
  u->context_();
  delete u;
  return 0;
}