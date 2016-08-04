

#ifndef SRC_NEURALNETWORK
#define SRC_NEURALNETWORK

#include <cstdlib>
#include <vector>
#include <memory>
#include <random>
class NeuralNetwork
{
	double sigmoid(double x);
	double randomWeight();
	double randomBias();

	std::normal_distribution<double>* distribution;
	std::default_random_engine generator;
public:
	static const int numInputNeurons = 3;
	static const int numOutputNeurons = 1;
	static const int numLayer1Neurons = 3;
	static const int numLayer2Neurons = 3;
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

	void Dump();
	void Initialize();
	double getOutput(int id);
	void setNeuronOutput(int id, double scale);
	void feedForward();
	std::unique_ptr<NeuralNetwork> Clone();
	std::unique_ptr<NeuralNetwork> Crossover(NeuralNetwork* other);
		
};


#endif
