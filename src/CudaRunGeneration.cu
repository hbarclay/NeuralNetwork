

// inline wrapper for cuBLAS call
__global__ void matrixMul()
{
	// optimized matrix multiplication
}

__global__ void launchEvals()
{
	// call matrixMul three times (different streams for each eval)
}

