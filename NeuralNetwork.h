
#ifndef SRC_NEURALNETWORK
#define SRC_NEURALNETWORK

#include<vector>

class NeuralNetwork
{


public:
	int numLayers;
	const int numInputNeurons;
	const int numOutputNeurons;
	const int numLayer1Neurons;
	const int numLayer2Neurons;
	
	struct Neuron
	{
		double bias = 0;
	}

	struct Connection
	{
		int from;
		int to;
		
		double weight;
	}

	std::vector<std::unique_ptr<Neuron>> neurons;
	std::vector<std::unique_ptr<Connection>> connections;	
};


#endif
