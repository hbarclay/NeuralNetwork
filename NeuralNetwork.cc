#include "NeuralNetwork.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <memory>
#include <random>

double NeuralNetwork::randomWeight()
{
	// FIXME possibly slow
	std::normal_distribution<double> distribution(0.0, 1.0);
	std::default_random_engine generator;
	double number = distribution(generator);
	return number;
}

double NeuralNetwork::randomBias()
{
	// FIXME possibly slow
	std::normal_distribution<double> distribution(0.0, 1.0);
	std::default_random_engine generator;
	double number = distribution(generator);
	return number;
}

void NeuralNetwork::Initialize()
{

	std::normal_distribution<double> distribution(0.0, 1.0);
	std::default_random_engine generator;

	//construct vector of neurons
	for(int i = 0; i < totalNeurons; i++ )
	{
		auto neuron = std::unique_ptr<Neuron>(new Neuron());
		double number = distribution(generator);
		neuron->bias = number;
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

	for(int i = 0; i < numLayer2Neurons; i++)
	{
		for(int j = 0; j < numOutputNeurons; j++)
		{
			auto connection = std::unique_ptr<Connection>(new Connection());
			connection->from = numInputNeurons + numLayer1Neurons + i;
			connection->to = numInputNeurons + numLayer1Neurons + numLayer2Neurons + j;
			connection->weight = randomWeight();
			connections.push_back(std::move(connection));	
		}
	}	
}

double NeuralNetwork::getOutput(int id)
{
	Neuron* neuron = neurons[id].get();
	return neuron->output;
}

void NeuralNetwork::setNeuronOutput(int id, double scale)
{
	Neuron* neuron = neurons[id].get();
	neuron->output = scale;
}

void NeuralNetwork::feedForward()
{
	for(unsigned i = numInputNeurons; i < totalNeurons; i++){
		Neuron* neuron = neurons[i].get();
		neuron->output = 0;
	}
	
	for(unsigned i = 0; i < totalConnections; i++){
		Connection* connection = connections[i].get();
		neurons[connection->to]->partialsum += 
			neurons[connection->from]->output * connection->weight;	
	}	
	
	for(unsigned i = numInputNeurons; i<totalNeurons; i++){
		Neuron* neuron = neurons[i].get();
		neuron->output = sigmoid(neuron->partialsum + neuron->bias);
	}
}

std::unique_ptr<NeuralNetwork> NeuralNetwork::Clone()
{
	std::unique_ptr<NeuralNetwork> clone(new NeuralNetwork);
	clone->Initialize();
	
	for(int i = 0; i < totalConnections; i++){
		clone->connections[i]->weight = this->connections[i]->weight;
	}

	for(int i = 0; i < totalNeurons; i++){
		clone->neurons[i]->bias = this->neurons[i]->bias;
	}

	return std::move(clone);
}

double NeuralNetwork::sigmoid(double x)
{
	return 1 / (1 + exp(-x));
}
