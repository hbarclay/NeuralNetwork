

#ifndef SRC_NEURALNETWORK
#define SRC_NEURALNETWORK

#include <vector>
#include <memory>

class NeuralNetwork
{
	double sigmoid(double x);
	double randomWeight();
	double randomBias();
public:
	static const int numInputNeurons = 10;
	static const int numOutputNeurons = 10;
	static const int numLayer1Neurons = 10;
	static const int numLayer2Neurons = 10;
	static const int totalNeurons = numInputNeurons + numOutputNeurons
		+ numLayer1Neurons + numLayer2Neurons;
	static const int totalConnections = 
		numInputNeurons * numLayer1Neurons +
		numLayer1Neurons * numLayer2Neurons +
		numLayer2Neurons * numOutputNeurons;
	
	struct Neuron
	{
		double partialsum = 0;
		double bias = 0;
		double output = 0;
	};

	struct Connection
	{
		int from;
		int to;
		
		double weight;
	};

	std::vector<std::unique_ptr<Neuron>> neurons;
	std::vector<std::unique_ptr<Connection>> connections;	

	void Initialize();
	double getOutput(int id);
	void setNeuronOutput(int id, double scale);
	void feedForward();
	std::unique_ptr<NeuralNetwork> Clone();

};


#endif
