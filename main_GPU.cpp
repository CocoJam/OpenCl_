#include<iostream>

#include <LinkedNode/LinkedNode.hpp>
#ifdef __APPLE__
#include <OpenCL/opencl.hpp>
#else
#include <CL/cl.hpp>
#endif
#include <vector>
#include <string>
#include <sstream> 
#define MAX_SOURCE_SIZE (0x100000)
int main(int argc, char const *argv[])
{   
    //get all platforms (drivers)
    std::vector<cl::Platform> all_platforms;
    cl::Platform::get(&all_platforms);
    if(all_platforms.size()==0){
        std::cout<<" No platforms found. Check OpenCL installation!\n";
        exit(1);
    }
    cl::Platform default_platform=all_platforms[0];
    std::cout << "Using platform: "<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";
 
    //get default device of the default platform
    std::vector<cl::Device> all_devices;
    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if(all_devices.size()==0){
        std::cout<<" No devices found. Check OpenCL installation!\n";
        exit(1);
    }
    cl::Device default_device=all_devices[0];
    std::cout<< "Using device: "<<default_device.getInfo<CL_DEVICE_NAME>()<<"\n";
 
 
   
 
    cl::Program::Sources sources;
 

    // kernel calculates for each element C=A+B
    std::string kernel_code=
            "   void kernel simple_add(global const int* A, global const int* B, global int* C){       "
            "       C[get_global_id(0)]=A[get_global_id(0)]+B[get_global_id(0)];                 "
            "   }                                                                       ";
    sources.push_back({kernel_code.c_str(),kernel_code.length()});
 
    cl::Program program(context,sources);
    if(program.build({default_device})!=CL_SUCCESS){
        std::cout<<" Error building: "<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device)<<"\n";
        exit(1);
    }
 
 
    // create buffers on the device
    cl::Buffer buffer_A(context,CL_MEM_READ_WRITE,sizeof(int)*10);
    cl::Buffer buffer_B(context,CL_MEM_READ_WRITE,sizeof(int)*10);
    cl::Buffer buffer_C(context,CL_MEM_READ_WRITE,sizeof(int)*10);
 
    int A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int B[] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0};
 
    //create queue to which we will push commands for the device.
    cl::CommandQueue queue(context,default_device);
 
    //write arrays A and B to the device
    queue.enqueueWriteBuffer(buffer_A,CL_TRUE,0,sizeof(int)*10,A);
    queue.enqueueWriteBuffer(buffer_B,CL_TRUE,0,sizeof(int)*10,B);
 
 
    //run the kernel
//     cl::KernelFunctor simple_add(cl::Kernel(program,"simple_add"),queue,cl::NullRange,cl::NDRange(10),cl::NullRange);
//     simple_add(buffer_A,buffer_B,buffer_C);
 
    //alternative way to run the kernel
    cl::Kernel kernel_add=cl::Kernel(program,"simple_add");
    kernel_add.setArg(0,buffer_A);
    kernel_add.setArg(1,buffer_B);
    kernel_add.setArg(2,buffer_C);
    queue.enqueueNDRangeKernel(kernel_add,cl::NullRange,cl::NDRange(10),cl::NullRange);
    queue.finish();
 
    int C[10];
    //read result C from the device to array C
    queue.enqueueReadBuffer(buffer_C,CL_TRUE,0,sizeof(int)*10,C);
 
    std::cout<<" result: \n";
    for(int i=0;i<10;i++){
        std::cout<<C[i]<<" ";
    }
 
    return 0;
}


// #include <stdio.h>	
// #include <stdlib.h>	
// #include <iostream>
// #ifdef __APPLE__	
// #include <OpenCL/opencl.h>	
// #else	
// #include <CL/cl.hpp>	
// #endif	
	
// #define MEM_SIZE (128)	
// #define MAX_SOURCE_SIZE (0x100000)	
	
// int main()	
// {	
// 	cl_platform_id platform_id = NULL;
// 	cl_device_id device_id = NULL;
// 	cl_context context = NULL;
// 	cl_command_queue command_queue = NULL;
// 	cl_mem memobj = NULL;
// 	cl_program program = NULL;
// 	cl_kernel kernel = NULL;
// 	cl_uint ret_num_devices;
// 	cl_uint ret_num_platforms;
// 	cl_int ret;
	
// 	float mem[MEM_SIZE];
	
// 	FILE *fp;
// 	const char fileName[] = "../kernel.cl";
// 	size_t source_size;
// 	char *source_str;
// 	cl_int i;
	
// 	/* Load kernel source code */
// 	fp = fopen(fileName, "r");
// 	if (!fp) {
//                 std::cout<< "File Not Found"<< std::endl;
// 	}
// 	source_str = (char *)malloc(MAX_SOURCE_SIZE);
// 	source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
// 	fclose(fp);
	
// 	/*Initialize Data */
// 	for (i = 0; i < MEM_SIZE; i++) {
                
// 	}
	
// 	/* Get platform/device information */
// 	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
// 	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
	
// 	/* Create OpenCL Context */
// 	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
	
// 	/* Create Command Queue */
// 	command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
	
// 	/* Create memory buffer*/
// 	memobj = clCreateBuffer(context, CL_MEM_READ_WRITE, MEM_SIZE * sizeof(float), NULL, &ret);
	
// 	/* Transfer data to memory buffer */
// 	ret = clEnqueueWriteBuffer(command_queue, memobj, CL_TRUE, 0, MEM_SIZE * sizeof(float), mem, 0, NULL, NULL);
	
// 	/* Create Kernel program from the read in source */
// 	program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);
	
// 	/* Build Kernel Program */
// 	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
	
// 	/* Create OpenCL Kernel */
// 	kernel = clCreateKernel(program, "vecAdd", &ret);
	
// 	/* Set OpenCL kernel argument */
// 	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj);
	
// 	size_t global_work_size[3] = {MEM_SIZE, 0, 0};
// 	size_t local_work_size[3] = {MEM_SIZE, 0, 0};
	
// 	/* Execute OpenCL kernel */
// 	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, global_work_size, local_work_size, 0, NULL, NULL);
	
// 	/* Transfer result from the memory buffer */
// 	ret = clEnqueueReadBuffer(command_queue, memobj, CL_TRUE, 0, MEM_SIZE * sizeof(float), mem, 0, NULL, NULL);
	
// 	/* Display result */
// 	for (i=0; i < MEM_SIZE; i++) {
	
// 	}
	
// 	/* Finalization */
// 	ret = clFlush(command_queue);
// 	ret = clFinish(command_queue);
// 	ret = clReleaseKernel(kernel);
// 	ret = clReleaseProgram(program);
// 	ret = clReleaseMemObject(memobj);
// 	ret = clReleaseCommandQueue(command_queue);
// 	ret = clReleaseContext(context);
	
// 	free(source_str);
	
// 	return 0;
// 	}