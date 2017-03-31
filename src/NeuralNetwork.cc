#include "NeuralNetwork.h"
#include "cblas.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <memory>
#include <random>
#include <chrono>
#include <cstring>

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
	unsigned seed  = std::chrono::system_clock::now().time_since_epoch().count();
	generator = *(new std::default_random_engine(seed));
	distribution = new std::normal_distribution<double>(0.0, 0.5);
	

	memset(outputs, 0, totalNeurons*sizeof(double));
	memset(biases, 0, totalNeurons*sizeof(double));
	memset(weights, 0, totalConnections*sizeof(double));

	for(int i = 0; i < totalNeurons; i++)
		biases[i] = randomBias();

	for(int i = 0; i < totalConnections; i++)
		weights[i] = randomWeight();
}

double NeuralNetwork::getOutput(int id)
{
	return outputs[id];
}

void NeuralNetwork::setNeuronOutput(int id, double scale)
{
	outputs[id] = scale;
}

void NeuralNetwork::feedForward()
{
	// m = 1, n = numLayer1Neurons, k = numInputNeurons
	// CblasRowMajor so LDA, LDB, and LDC are column counts
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
			1, numLayer1Neurons, numInputNeurons, 
			1.0, 
			outputs, numInputNeurons, 
			weights, numLayer1Neurons, 
			1.0, 
			outputs + numInputNeurons, numLayer1Neurons);


	for(int i = numInputNeurons; i<numInputNeurons+numLayer1Neurons; i++)
	{
		outputs[i] = sigmoid(outputs[i] + biases[i]);
	}

	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
			1, numLayer2Neurons, numLayer1Neurons,
			1.0,
			outputs + numInputNeurons, numLayer1Neurons,
			weights + (numInputNeurons*numLayer1Neurons), numLayer2Neurons,
			1.0,
			outputs + numInputNeurons + numLayer1Neurons, numLayer2Neurons);

	for(int i = numInputNeurons + numLayer1Neurons; i<numInputNeurons+numLayer1Neurons + numLayer2Neurons; i++)
	{
		outputs[i] = sigmoid(outputs[i] + biases[i]);
	}

	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
			1, numOutputNeurons, numLayer2Neurons,
			1.0,
			outputs + numInputNeurons + numLayer1Neurons, numLayer2Neurons,
			weights + (numInputNeurons*numLayer1Neurons) + (numLayer1Neurons*numLayer2Neurons), numOutputNeurons,
			1.0,
			outputs + numInputNeurons + numLayer1Neurons + numLayer2Neurons, numOutputNeurons);

	for(int i = numInputNeurons + numLayer1Neurons + numLayer2Neurons; i<totalNeurons; i++)
	{
		outputs[i] = sigmoid(outputs[i] + biases[i]);
	}

/*
	Tested reference usage:

	double in1[3] = {5, 6, 7};
	double in2[12] = {1, 2, 3, 4,
			1, 2, 3, 4,
			1, 2, 3, 4};
	
	double c[4];

	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
			1, 4, 3,
			1.0,
			in1, 3,
			in2, 4,
			1.0,
			c, 4);
*/
}

std::unique_ptr<NeuralNetwork> NeuralNetwork::Clone()
{
	std::unique_ptr<NeuralNetwork> clone(new NeuralNetwork);
	clone->Initialize();

	for(int i = 0; i < totalConnections; i++) {
		clone->weights[i] = this->weights[i];
	}

	for(int i = 0; i < totalNeurons; i++) {
		clone->biases[i] = this->biases[i];
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
			offspring->weights[i] = this->weights[i];	
		} else {
			offspring->weights[i] = other->weights[i];
		}
	}

	for(int i = 0; i < totalNeurons; i++){
		double num = 1.0 * rand() / RAND_MAX;
		if(num < 0.5){
			offspring->biases[i] = this->biases[i];
		} else {
			offspring->biases[i] = other->biases[i];
		}
	}

	return std::move(offspring);
}

double NeuralNetwork::sigmoid(double x)
{
	double a = (1.0 / (1.0 + exp(-x)));
//	std::cout << a << " ";
	return a;
}

