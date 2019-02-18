#ifndef __Kernels_Utils_PlatForm_H_
#define __Kernels_Utils_PlatForm_H_

#ifdef __APPLE__
#include <OpenCL/opencl.hpp>
#else
#include <CL/cl.hpp>
#endif
#include <iostream>
#include <algorithm>
#include<unordered_map>
#include <tuple>
#include "Device.hpp"

/*
Plaform class coonsist of invidiaul platform based on the comp's
platform.
Util::Platform is the wrapper class of cl::Platform
That is compose of cl::Device or Util::Device (Wrapper class of cl::Device with inhertence)
*/

namespace Util
{
    template<class D>
    class Platform
    {

/*
template of D is only avalible for cl::Device or Util::Device.
platform is the current default platform, cl::Platform. Assigned during constructor.
all_devices vec of all devices witin the platform only asscessible by private methos;
context is platform specific, one cl::Context per platform
ciErrNUM OpenCL provoided error detection cl_int.
GetDevice_ is a private method for accessing the devices of current platform.
context_ is a private method for applying context according to given cl::Device/ vec<cl::Device>
/ Util::Device/ vec<Util::Device>


*/
    private:
        cl::Platform platform;
        std::vector<D> all_devices;
        cl::Context context;
        cl::CommandQueue queue;
        cl_int ciErrNum = CL_SUCCESS;
        std::unordered_map<std::string,std::tuple<cl::Program,cl::Kernel>> ProgramMap;
        std::vector<D> GetDevice_(cl::Platform& plateform, int cl_type);
        template<class T>
        cl::Context context_(T device);
        template<class T, class T2>
        cl_int release_(cl_int (*func) (T), T2 item, std::string str);
        


/*
    GetDevice() is used to obtain/ getter method for vec<D>, which consist fail safe for vec init.
        Auto run GetDevice_ is needed.
    GetDevice(cl::Platform) accessing method of all devices within given platform.
    
*/

    public:
        Platform(cl::Platform platform);
        ~Platform();
        std::vector<D> GetDevice();        
        std::vector<D> GetDevice(cl::Platform& plateform);
        std::vector<D> GetDevice(cl::Platform& plateform, int cl_type);
        cl::Context setContext();
        cl::Context setContext(D device);
        cl::Context setContext(std::vector<D> device);
        cl::CommandQueue setQuene();
        cl::CommandQueue setQuene(cl::Context);
        // cl::Program program_quene(const char* filename, std::string methodname, bool buildKernel = true);
        // cl::Program program_quene(const char* filename, const char* methodname,bool buildKernel = true);
        cl::Program program_quene(const char * filename, bool buildKernel=true);
        cl::Program program_quene(const char * filename, const char *  methodname, bool buildKernel = true);
        // cl_program program_quene(char[] filename);
        std::unordered_map<std::string, std::tuple<cl::Program,cl::Kernel>> getProgramMap();
    };


} // Utils
#endif