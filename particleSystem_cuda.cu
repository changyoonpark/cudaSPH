#include "particleSystem_cuda.cuh"

void DeviceMemoryPointers::cleanUpDevice(){

	cout << "Device Cleaned Up." << endl;

	cudaFree(this->pos);
	cudaFree(this->vel);
	cudaFree(this->acc);

}

void MemoryOperations::printVector(vector<float4> v){
	for (int i=0;i<v.size();i++){
		cout << v[i].x << "," << v[i].y << "," << v[i].z << endl;
	}
}

void MemoryOperations::foo(vector<float4> v){
	float* foofoo = (float*) v.data();
	cout << "HAHA" << endl;
	for (int i=0;i<v.size();i++){
		cout << foofoo[i] << endl;
	}
	cout << "HAHA" << endl;
}


void MemoryOperations::deviceToHostCopy(
	vector<float4>* hostVector,
	float* devMem){

	cudaMemcpy(hostVector->data(),
			   devMem,
			   hostVector->size() * sizeof(float) * 4,
			   cudaMemcpyDeviceToHost);

}

void MemoryOperations::hostToDeviceCopy(
	vector<float4>* hostVector,
	float* devMem){
	
	cudaMemcpy(devMem,
			   (float*) hostVector->data(),
			   hostVector->size() * sizeof(float) * 4,
			   cudaMemcpyHostToDevice);

}

