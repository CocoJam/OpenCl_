#include "OCL.h"

#include <filesystem>
OCL::OCL(const char* preferred): 
        context(NULL),
        // device(std::vector<cl_device_id>),
        commandQueue(NULL),
        // program(std::vector<cl_program>),
        // kernel(std::vector<cl_kernel>),
        platformVersion(OPENCL_VERSION_1_2),
        deviceVersion(OPENCL_VERSION_1_2),
        compilerVersion(OPENCL_VERSION_1_2){
            setup();
        };
OCL::~OCL(){
    release_<cl_context>(clReleaseContext, this->context, "context");
    release_<cl_command_queue>(clReleaseCommandQueue, this->commandQueue, "queue");
    release_<cl_program>(clReleaseProgram, this->program, "Program");
    release_<cl_kernel>(clReleaseKernel, this->kernel, "Kernel");
    std::cout<< "destory OCL object" <<std::endl;
}



void OCL::setup(const char* preferred){
    p("start")
    try{
    cl_platform_id platform_ptr = preferred_platform(preferred);
    cl_int err = CL_SUCCESS;
    size_t stringLength = 0;
    err = clGetPlatformInfo(platform_ptr, CL_PLATFORM_NAME, 0, NULL, &stringLength);
    std::vector<char> platformName(stringLength);
    err = clGetPlatformInfo(platform_ptr, CL_PLATFORM_NAME, stringLength, &platformName[0], NULL);
    std::string str(platformName.begin(),platformName.end());
    p(str)
    cl_uint num =  num_of_platform_device(platform_ptr, CL_DEVICE_TYPE_GPU);
    this->device = platform_device(platform_ptr, CL_DEVICE_TYPE_GPU);
    this->context = context_with_properties(this->device[0],platform_ptr,NULL, this->device.size());
    std::vector<cl_command_queue> queue(device.size());
    for(int i=0;i<queue.size();i++){
        queue[i] = commandQuene(device[i],context);
    }
    this->commandQueue = queue;
    p("end")
    }
    catch_block(this);
}

template<class T>
void OCL::release_(cl_int (*func) (T), std::vector<T> item, std::string str){
    for(int i=0;i< item.size();i++){
        release_<T>(func,(T) item[i], str);
    }
}

template<class T>
cl_int OCL::release_(cl_int (*func) (T), T item, std::string str){
    auto item_ptr = item;
   if(&item == NULL){
            std::cout<< str << " is NULL"<< std::endl;
            return CL_INVALID_EVENT;
        }
        cl_int err = func(item_ptr);
    if(err == CL_SUCCESS){
            std::cout<< str <<" released"<<std::endl;
        }
        else if(&item == NULL){
            std::cout<< str <<" not released, due to Null of "<< str<<std::endl;
        }
        else{
                std::cout<< str <<" not released"<<std::endl;        
        }
        return err;
}

cl_platform_id OCL::preferred_platform(const char* preffered_platform){
    cl_uint numPlatforms = 0;
    cl_int err = CL_SUCCESS;
    size_t stringLength = 0;
     err = clGetPlatformIDs(0, NULL, &numPlatforms);
    if (CL_SUCCESS != err)
    {
        throw  std::invalid_argument(throw_error("get clGetPlatformID() not functioning"," ",OpenCLError(err)));
        return NULL;
    }
    if(numPlatforms < 1){
        throw  std::invalid_argument("less than 1 number of platform");        
        return NULL;
    }
    
    std::vector<cl_platform_id> platforms(numPlatforms);
    
     if(preffered_platform != NULL){
         try{
            platform_to_vec(&platforms[0],numPlatforms);        
         }catch(std::invalid_argument& e){
             std::cout<< e.what()<<std::endl;
             throw;
             return NULL;
         }
        for(int i=0;i<numPlatforms;i++){
            err = clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 0, NULL, &stringLength);
            std::vector<char> platformName(stringLength);
            err = clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, stringLength, &platformName[0], NULL);
            if(err!= CL_SUCCESS){
                    throw  std::invalid_argument(throw_error("get clGetPlatformInfo() not functioning"," ",OpenCLError(err)));
                    return NULL;
                }
                if (strstr(&platformName[0], preffered_platform) != 0)
                {   
                    std::string str(platformName.begin(),platformName.end());
                    return platforms[i];
                }
        }
    }else{
        try{
            platform_to_vec(&platforms[0],numPlatforms);        
         }catch(std::invalid_argument& e){
             std::cout<< e.what()<<std::endl;
             throw;
             return NULL;
         }
        return platforms[0];
    }
}

void OCL::platform_to_vec(cl_platform_id* platform_vector_id, cl_uint numPlatforms){
    cl_int err = CL_SUCCESS;
    err = clGetPlatformIDs(numPlatforms, platform_vector_id, NULL);
         if (CL_SUCCESS != err)
        {   
            throw  std::invalid_argument(throw_error("get clGetPlatformID() not functioning of:"," ",OpenCLError(err)));        
            // return NULL;
        }
        
    // return platform_vector_id;
}

std::vector<cl_device_id> OCL::platform_device(cl_platform_id platform_id,cl_device_type deviceType, cl_uint numDevices){
    if(numDevices <1){
       numDevices  = num_of_platform_device(platform_id,deviceType);
        if(numDevices <1){
            throw std::invalid_argument(throw_error("Less than 1 number of Devices"));
        }
    }
    std::vector<cl_device_id> device_to_vector(numDevices);
    try{
        device_to_vec(platform_id, &device_to_vector[0], deviceType, numDevices);
    }
    rethrow_block;
    return device_to_vector;
}

cl_uint OCL::num_of_platform_device(cl_platform_id platform_id, cl_device_type deviceType){
    cl_uint num_of_devices = 0;
    
    cl_int err = CL_SUCCESS;
    size_t stringLength = 0;
    err = clGetPlatformInfo(platform_id, CL_PLATFORM_NAME, 0, NULL, &stringLength);
    std::vector<char> platformName(stringLength);
    err = clGetPlatformInfo(platform_id, CL_PLATFORM_NAME, stringLength, &platformName[0], NULL);
    std::string str(platformName.begin(),platformName.end());
    
    err = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU,0,0,&num_of_devices);
    
    
    if(err != CL_SUCCESS){
        throw std::invalid_argument(throw_error("can not access number of devices"," ",OpenCLError(err)));
    }
    return num_of_devices;
}

void OCL::device_to_vec( cl_platform_id platform_vector_id, cl_device_id* device_vector_id, cl_device_type deviceType, cl_uint numDevices){
    cl_int err = CL_SUCCESS;
    err = clGetDeviceIDs(platform_vector_id, deviceType, numDevices, device_vector_id, NULL);
        if (CL_SUCCESS != err)
        {
            throw  std::invalid_argument(throw_error("get clGetDeviceIDs() not functioning and device"," ",OpenCLError(err)));        
            // return NULL;
        }
    // return device_vector_id;
}

cl_context OCL::context_with_properties(cl_device_id device_vector_id, cl_platform_id platform_vector_id ,cl_context_properties contextProperties[],cl_uint numdevices){
    cl_int err = CL_SUCCESS;
    if(numdevices == 0){
        throw std::invalid_argument("Lack of devices for create context");
        return NULL;
    }
    if(contextProperties == NULL){
       cl_context_properties contextProperties[]={CL_CONTEXT_PLATFORM, (cl_context_properties)platform_vector_id, 0};
    }

    this->context = clCreateContext(&contextProperties[0], numdevices, &device_vector_id, 0, 0, &err);
     if ((CL_SUCCESS != err) || (NULL == this->context))
    {
        throw  std::invalid_argument(throw_error("get clCreateContextFromType() not within this plafrom"," ",OpenCLError(err)));
        return NULL;
    }
    return this->context; 
}

cl_context OCL::context_with_properties(cl_platform_id platform_vector_id ,cl_context_properties contextProperties[],cl_device_type deviceType){
    cl_int err = CL_SUCCESS;
    if(contextProperties == NULL){
       cl_context_properties contextProperties[]={CL_CONTEXT_PLATFORM, (cl_context_properties)platform_vector_id, 0};
    }
    this->context = clCreateContextFromType(contextProperties, deviceType, NULL, NULL, &err);
     if ((CL_SUCCESS != err) || (NULL == this->context))
    {
        throw  std::invalid_argument(throw_error("get clCreateContextFromType() not within this plafrom"," ",OpenCLError(err)));
        return NULL;
    }
    return this->context; 
}

cl_command_queue OCL::commandQuene(cl_device_id device_id, cl_context context_id){
    cl_int err = CL_SUCCESS;
    const cl_command_queue_properties properties[] = {CL_QUEUE_PROPERTIES, CL_QUEUE_PROFILING_ENABLE, 0};
    cl_command_queue queue = clCreateCommandQueueWithProperties(context_id, device_id, properties, &err);
      if (CL_SUCCESS != err)
        {
            throw  std::invalid_argument(throw_error("get clCreateCommandQueueWithProperties() not functioning platform and device"," ",OpenCLError(err)));        
            return NULL;
        }
    return queue;
}

cl_program OCL::prgoramWithSource(cl_context context, const char* fileName){
    char* source = NULL;
    size_t src_size = 0;
    cl_int err = CL_SUCCESS;
    try{
        programSourceFileReader(fileName, &source, &src_size);
    }
    rethrow_block;
    cl_program program = clCreateProgramWithSource(context, 1, (const char**)&source, &src_size, &err);
    if(err!= CL_SUCCESS){
        throw std::invalid_argument(throw_error("Program can not be created"," ",OpenCLError(err)));
        return NULL;
    }
    delete source;
    return program;
}

void OCL::programSourceFileReader(const char* fileName, char** source_ptr, size_t* src_size){
    char buf[4096];
    std::cout  << "CWD: " << cwd(buf, sizeof buf) << std::endl;
    std::ifstream infile; 
    infile.open(fileName, std::ifstream::binary);
    if(infile){
        infile.seekg(0, infile.end);
        *src_size =(size_t)infile.tellg();
        infile.seekg (0, infile.beg);
        *source_ptr = new char [*src_size];
        infile.read (*source_ptr,*src_size);
        infile.close();
    }else{
        char buf[4096];
        std::cout  << "CWD: " << cwd(buf, sizeof buf) << std::endl;
        throw std::invalid_argument(throw_error("File: ",fileName," can not be opened"));
    }
    return;
}

cl_program OCL::programBuild(cl_program program, cl_uint numOfDevices, cl_device_id* device_vector_id, const char* option){
    cl_int err = CL_SUCCESS;
    err = clBuildProgram(program, numOfDevices, (const cl_device_id*)device_vector_id, option, 0,0);
    if(err == CL_BUILD_PROGRAM_FAILURE){
        for(int i=0;i< (size_t)numOfDevices; i++){
            size_t log_length = 0;
            err = clGetProgramBuildInfo(program,device_vector_id[i],CL_PROGRAM_BUILD_LOG,0,0,&log_length);
            std::vector<char> log(log_length);
            err = clGetProgramBuildInfo(program,device_vector_id[i],CL_PROGRAM_BUILD_LOG, log_length, &log[0], 0);
            throw std::invalid_argument(throw_error(std::string(&log[0])," ",OpenCLError(err)));
        }
    }
    if(err == CL_INVALID_DEVICE){
            std::stringstream ss;
            ss<< OpenCLError(err)<<" Devices of "<< numOfDevices<<" available->";
            size_t stringLength = 0;
            err= clGetDeviceInfo(device_vector_id[0],CL_DEVICE_AVAILABLE,0,NULL,&stringLength);
            std::vector<cl_bool> DeviceAvailable(stringLength/sizeof(cl_bool));
            err= clGetDeviceInfo(device_vector_id[0],CL_DEVICE_AVAILABLE,stringLength,&DeviceAvailable[0],NULL);
            for(int j=0;j<DeviceAvailable.size();j++){
                ss<<" "<<DeviceAvailable[j];
            }
            throw std::invalid_argument(throw_error(ss.str()));
    }
    if(err != CL_SUCCESS){
        throw std::invalid_argument(throw_error(OpenCLError(err)));
    }
    return program;
}

cl_kernel OCL::kernelBuild(cl_program program, const char* fileName){
    cl_int err = CL_SUCCESS;
    cl_kernel kernel = clCreateKernel(program, fileName, &err);
    if(err!=CL_SUCCESS){
        throw std::invalid_argument(throw_error("Kernerl Build error"," with building name of ",fileName, " ",OpenCLError(err)));
    }
    return kernel;
}




