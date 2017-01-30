#include "globalDefs.h"

SimulationParameters::SimulationParameters(){
	minParticleDiameter = 0.1f;

	worldSize = make_float3(2.0f,2.0f,2.0f);
	worldCorner1 = make_float3(0.0f,0.0f,0.0f);
	worldCorner2 = worldCorner1 + worldSize;

	cellSize = worldSize.x / 16.0f;

}

float randFloat(){
	return static_cast<float>(std::rand()) / RAND_MAX;
}