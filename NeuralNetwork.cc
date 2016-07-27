#include "NeuralNetwork.h"
#include <iostream>
#include <cstdlib>




double NeuralNetwork::randomWeight()
{
	return ((double) rand() / (RAND_MAX)) * 2.0 - 1;
}


void Initialize()
{
	//construct vector of neurons
	for(int i = 0; i < totalNeurons; i++ )
	{
		auto neuron = std::unique_ptr<Neuron>(new Neuron());
		neuron->bias = randomBias();
		neurons.push_back(std::move(neuron));
	}

	//construct vector of connections
	for(int i = 0; i < numInputNeurons; i++)
	{
		for(int j = 0; j < numLayer1Neurons; j++)
		{
			auto connection = std::unique_ptr<Connection>(new Connection());
			connection->from = i;
			connection->to = numInputNeurons + j;
			connection->weight = randomWeight();
			connections.push_back(std::move(connection));
		}
	}


	for(int i = 0; i < numLayer1Neurons; i++)
	{
		for(int j = 0; j < numLayer2Neurons; j++)
		{
			auto connection = std::unique_ptr<Connection>(new Connection());
			connection->from = numInputNeurons + i;
			connection->to = numInputNeurons + numLayer1Neurons + j;
			connection->weight = randomWeight();
			connections.push_back(std::move(connection));
		}
	}

	for(int i = 0; i < numLayet2Neurons; i++)
	{
		for(int j = 0; j < numOutputNeurons; j++)
		{
			auto connection = std::unique_ptr<Connection>(new Connection());
			connection->from = numInputNeurons + numLayer1Nerons + i;
			connection->to = numInputNeurons + numLayer1Neurons + numLayer2Neurons + j;
			connection->weight = randomWeight();
			connections.push_back(std::move(connection));	
		}
	}	
}

double NeuralNetwork::getOutput(int neuron)
{
	
}

void NeuralNetwork::setNeuronOutput(int neuron, double scale)
{

}

void NeuralNetwork::feedForward()
{

}

double NeuralNetwork::sigmoid(double x)
{
	return 1 / (1 + exp(-x));
}
