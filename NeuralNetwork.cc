#include "NeuralNetwork.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <memory>
#include <random>

double NeuralNetwork::randomWeight()
{
	double number = (*distribution)(generator);
	return number;
}

double NeuralNetwork::randomBias()
{
	double number = (*distribution)(generator);
	return number;
}

void NeuralNetwork::Initialize()
{
	distribution = new std::normal_distribution<double>(0.0, 1.0);

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


std::unique_ptr<NeuralNetwork> NeuralNetwork::Crossover(NeuralNetwork* other)
{
	std::unique_ptr<NeuralNetwork> offspring(new NeuralNetwork());
	offspring->Initialize();

	for(int i = 0; i < totalConnections; i++){
		double num = 1.0 * rand() / RAND_MAX;
		if(num < 0.5){
			offspring->connections[i]->weight = this->connections[i]->weight;	
		} else {
			offspring->connections[i]->weight = other->connections[i]->weight;
		}
	}

	for(int i = 0; i < totalNeurons; i++){
		double num = 1.0 * rand() / RAND_MAX;
		if(num < 0.5){
			offspring->neurons[i]->bias = this->neurons[i]->bias;
		} else {
			offspring->neurons[i]->bias = other->neurons[i]->bias;
		}
	}

	return std::move(offspring);
}

double NeuralNetwork::sigmoid(double x)
{
	return 1 / (1 + exp(-x));
}
