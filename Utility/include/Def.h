#ifndef __def__H__
#define __def__H__
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#define rethrow_block\
    catch(std::invalid_argument& e){\
        std::cout << e.what() << "\nCaugh Error at "<<__LINE__<<" at "<<__FILE__<<"\n";\
        throw;\
    }
#define catch_block\
    catch(std::invalid_argument& e){\
        std::cout << e.what() << "\nCaugh Error at "<<__LINE__<<" at "<<__FILE__<<"\n";\
        std::cout << "Program Exit(EXIT_FAILURE) terminating."<< "\n";\
        exit(EXIT_FAILURE);\
    }
#define p(x)\
    std::cout<<x<<"\n";

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