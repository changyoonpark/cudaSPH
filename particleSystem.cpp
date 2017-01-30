#include "particleSystem.h"
#include "displayFunctions.h"
// #include <cuda_gl_interop.h>

using namespace std;

ParticleSystem::ParticleSystem(uint numParticles){
	// readInitialPositionFile();
	cout << "Initializing particle System." << endl;	
	generateInitialPositions();
	cout << "Allcoated size : " << hostMem.pos.size() << endl; 
	allocateDevicePositionMemory(hostMem.pos.size());

	this->maxParticleDiameter = 0.1f;
}

void ParticleSystem::setVertexBuffer(uint vbo){
	memVbo = vbo;
}

void ParticleSystem::allocateDevicePositionMemory(uint numParticles){
	//Allocate memory on GPU.
	//Register the VBO with CUDA.
	cout << "Allocating (" << numParticles << ") particles on the device" << endl;
	posVbo = DisplayFunctions::createVbo(numParticles * sizeof(float) * 4); // This allocated GPU memory thru GL
	cout << "Allcated with VBO : " << posVbo << endl;

	cudaGraphicsGLRegisterBuffer(&devicePosReference,
								 posVbo,
								 cudaGraphicsMapFlagsNone);
}

void ParticleSystem::timeStep(){
	// float* dPos;	
	//&devicePosVbo was allocated by GL.
	//by doing the below, dPos is now accessable by cuda.
	//Cuda Operations should be placed between the mapping/unmapping.
    devMem.pos = (float *) DisplayFunctions::mapGLBufferObject(&devicePosReference);	

	MemoryOperations::hostToDeviceCopy(&(hostMem.pos),
									   devMem.pos);

    DisplayFunctions::unmapGLBufferObject(&devicePosReference);    
}

void ParticleSystem::generateInitialPositions(){
	// Generates initial positions on the host.
	float spacing = 0.1;
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			for (int k=0;k<10;k++){		
				cout << i << j << k	<< endl;
				hostMem.pos.push_back(make_float4(spacing * i - 0.5, spacing * j - 0.5, spacing * k - 0.5,1.0));							
				hostMem.vel.push_back(make_float4(randFloat(),randFloat(),randFloat(),0));
			}
		}
	}
	// vel.resize(pos.size());
	hostMem.acc.resize(hostMem.pos.size());
	numParticles = hostMem.pos.size();
}

void ParticleSystem::readInitialPositionFile(){
	cout << "Not Implemented Yet." << endl;
}
