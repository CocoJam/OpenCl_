#ifndef __def__H__
#define __def__H__
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <vector>
#ifdef _WIN32
#include <direct.h>
#define cwd _getcwd
#define cd _chdir
#else
#include "unistd.h"
#define cwd getcwd
#define cd chdir
#endif
#ifdef __APPLE__
#include <OpenCL/opencl.hpp>
#else
#include <CL/cl.hpp>
#endif

#define rethrow_block\
    catch(std::invalid_argument& e){\
        std::cout << e.what() << "\nCaugh Error at "<<__LINE__<<" at "<<__FILE__<<"\n";\
        throw;\
    }
#define catch_\
    catch(std::invalid_argument& e){\
        std::cout << e.what() << "\nCaugh Error at "<<__LINE__<<" at "<<__FILE__<<"\n";\
        std::cout << "Program Exit(EXIT_FAILURE) terminating."<< "\n";\
        exit(EXIT_FAILURE);\
    }
#define catch_block(d)\
    catch(std::invalid_argument& e){\
        std::cout << e.what() << "\nCaugh Error at "<<__LINE__<<" at "<<__FILE__<<"\n";\
        std::cout << "Program Exit(EXIT_FAILURE) terminating."<< "\n";\
        delete d;\
        exit(EXIT_FAILURE);\
    }
#define throw_error(...)\
    LogAll( __VA_ARGS__," at ",__LINE__," ",__FILE__)
#define p(x)\
    std::cout<<x<<"\n";
#define getInfoVec(x,x1,x2,vec,type)\
  size_t arg_length = 0;\
  x(x1,x2,0,0,&arg_length);\
  vec.resize(arg_length/sizeof(type));\
  x(x1,x2,arg_length,&vec[0],NULL);
#define getArgVec(x,x1,x2,x3,vec)\
  size_t arg_length =0;\
  x(x1,x2,x3,0,0,&arg_length);\
  x(x1,x2,x3,arg_length,&vec[x2],NULL);

const char* OpenCLError(cl_int errorCode);
template<typename T,typename... Args>
void concat_stream(std::stringstream& ss,T t ,Args... args){
    concat_stream(ss, t);
    concat_stream(ss, args...);
}
template <typename T>
void concat_stream(std::stringstream& o, T t)
{
    o << t;
}
template<typename... Args>
std::string LogAll(Args... args)
{
    std::stringstream oss;
    concat_stream(oss, args...);
    return oss.str();
}
#endif