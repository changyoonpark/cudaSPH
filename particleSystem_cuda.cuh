#ifndef PARTICLE_SYSTEM_CUDA_H
#define PARTICLE_SYSTEM_CUDA_H

#include <iostream>
#include <vector>
#include "cuda_runtime.h"

// #include "globalDefs.h"

using namespace std;

class MemoryOperations{
public:
	static void printVector(vector<float4> v);
	static void foo(vector<float4> v);
	static void deviceToHostCopy(vector<float4>* host, float* device);
	static void hostToDeviceCopy(vector<float4>* host, float* device);
};

class HostMemoryPointers{
public:
	vector<float4> pos;
	vector<float4> vel;
	vector<float4> acc;
};

class DeviceMemoryPointers{
public:
	void cleanUpDevice();

	float* pos;
	float* vel;
	float* acc;
};

#endif