
__global__ void matrixMul()
{
	// optimized matrix multiplication
}

__global__ void launchEvals()
{
	// call matrixMul three times (different streams for each eval)
}

void launchEvals(std::vector<std::unique_ptr<NeuralNetwork>>& individuals)
{

	// copy all data to global memory

	// call launch Evals


}
