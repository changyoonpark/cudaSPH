#include <vector>
#include <cuda_runtime.h>
// #include "globalDefs.h"

using namespace std;

class SolverFunctions{
public:
	void forwardEulerCPU(vector<float> v, vector<float> vp, float dt);
};