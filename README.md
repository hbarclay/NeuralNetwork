# NeuralNetwork

This is a very simple implementation of a Genetic Algorithm to train a Neural Network to recognize handwritten digits (from the MNIST database). It has been an interesting exercise in that the algorithm used is far from optimal for such a problem, and so requires careful tuning to find optimal weights. OpenBLAS was used to accelerate the feed-forward operation, and I intend to eventually write a OpenCL or CUDA implementation to explore possible speed improvements offered by parallelization.

## Setup

### Build OpenBLAS
  Build OpenBLAS with `make`, then run `make install PREFIX=/path/to/OpenBLAS-build`
  
