

#ifndef INCLUDE_NEURALNETWORK_H_
#define INCLUDE_NEURALNETWORK_H_

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
	static const int numInputNeurons = 784;
	static const int numOutputNeurons = 10;
	static const int numLayer1Neurons = 50;
	static const int numLayer2Neurons = 50;

	static const int totalNeurons = numInputNeurons + numOutputNeurons
		+ numLayer1Neurons + numLayer2Neurons;
	static const int totalConnections = 
		numInputNeurons * numLayer1Neurons +
		numLayer1Neurons * numLayer2Neurons +
		numLayer2Neurons * numOutputNeurons;

	static const int layer1Offset = numInputNeurons;
	static const int layer2Offset = layer1Offset + numLayer1Neurons;
	static const int outputLayerOffset = layer2Offset + numLayer2Neurons;

	double weights[totalConnections];
	double biases[totalNeurons];
	double outputs[totalNeurons];

	void Dump();
	void Initialize();
	double getOutput(int id);
	void setNeuronOutput(int id, double scale);
	void feedForward();
	std::unique_ptr<NeuralNetwork> Clone();
	std::unique_ptr<NeuralNetwork> Crossover(NeuralNetwork* other);
		
};


#endif // INCLUDE_NEURAL_NETWORK_H_
