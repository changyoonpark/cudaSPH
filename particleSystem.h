#include <vector>

#include "particleSystem_cuda.cuh"
#include "globalDefs.h"

// #include "cuda_runtime.h"

using namespace std;

class ParticleSystem{

public:
	HostMemoryPointers hostMem;
	DeviceMemoryPointers devMem;

	uint memVbo;
	uint posVbo;
	uint colorVbo;

	cudaGraphicsResource_t devicePosReference;
	cudaGraphicsResource_t deviceColorVbo;


	uint numParticles;
	float maxParticleDiameter;

	ParticleSystem(uint numParticles);
	void timeStep();

private:

	void generateInitialPositions();
	void allocateDevicePositionMemory(uint number);
	void setVertexBuffer(uint vbo);
	void readInitialPositionFile();

};
