#ifndef GLOBAL_DEFS_H
#define GLOBAL_DEFS_H


#include "inc/mathHelper.h"
#include <cstdlib>
#include <ctime>



class SimulationParameters{
public:
	float maxParticleDiameter;

	float3 worldSize;
	float3 worldCorner1;
	float3 worldCorner2;

	float cellSize;
	SimulationParameters();
};

float randFloat();
#endif

