
#ifndef SRC_NEURALNETWORK
#define SRC_NEURALNETWORK

#include<vector>

class NeuralNetwork
{
	double sigmoid(double x);
	double randomWeight();
	double randomBias();
public:
	int numLayers;
	const int numInputNeurons;
	const int numOutputNeurons;
	const int numLayer1Neurons;
	const int numLayer2Neurons;
	const int totalNeurons = numInputNeurons + numOutPutNeurons
		+ numLayer1Neurons + numLayer2Neurons;
	const int totalConnections = 
		numInputNeurons * numLayer1Nuerons +
		numLayer1Neurons * numLayer2Neurons +
		numLayer2Neurons * numOutputNeurons;
	
	struct Neuron
	{
		double bias = 0;
		double output = 0;
	}

	struct Connection
	{
		int from;
		int to;
		
		double weight;
	}

	std::vector<std::unique_ptr<Neuron>> neurons;
	std::vector<std::unique_ptr<Connection>> connections;	

	void Initialize();
	double getOutput(int neuron);
	void setNeuronOutput(int neuron, double scale);
	void feedForward();
	std::unique_ptr<NeuralNetwork> Clone();

};


#endif
