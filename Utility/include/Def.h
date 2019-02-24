#ifndef __def__H__
#define __def__H__
#define rethrow_block\
    catch(std::invalid_argument& e){\
        std::cout << e.what() << "\nCaugh Error at "<<__LINE__<<" at "<<__FILE__<<"\n";\
        throw;\
    }
#define catch_block\
    catch(std::invalid_argument& e){\
        std::cout << e.what() << "\nCaugh Error at "<<__LINE__<<" at "<<__FILE__<<"\n";\
    }

#endif