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
/*		
	int num = numInputNeurons * numLayer1Neurons;

	for(unsigned i = 0; i < num; i++){
		Connection* connection = connections[i].get();
		neurons[connection->to]->partialsum += 
			neurons[connection->from]->output * connection->weight;	
	}	

	for(unsigned i = numInputNeurons; i < numInputNeurons + numLayer1Neurons; i++){
		Neuron* neuron = neurons[i].get();
		neuron->output = sigmoid(neuron->partialsum + neuron->bias);
	}

	for(unsigned i = num; i < num + numLayer1Neurons * numLayer2Neurons; i++){
		Connection* connection = connections[i].get();
		neurons[connection->to]->partialsum += 
			neurons[connection->from]->output * connection->weight;	
	}
	
	for(unsigned i = numInputNeurons+ numLayer1Neurons; i<numInputNeurons+numLayer1Neurons+numLayer2Neurons; i++){
		Neuron* neuron = neurons[i].get();
		neuron->output = sigmoid(neuron->partialsum + neuron->bias);
	}
	
	for(unsigned i = num + numLayer1Neurons * numLayer2Neurons; i < totalConnections; i++){
		Connection* connection = connections[i].get();
		neurons[connection->to]->partialsum += 
			neurons[connection->from]->output * connection->weight;	
	}

	for(unsigned i = numInputNeurons+numLayer1Neurons+numLayer2Neurons; i < totalNeurons; i++){
		Neuron* neuron = neurons[i].get();
		neuron->output = sigmoid(neuron->partialsum + neuron->bias);
	}
*/

	for(int i = numInputNeurons; i<numInputNeurons+numLayer1Neurons; i++) {
		double out = 0;
		int x = (i-numInputNeurons)*numInputNeurons;	
		cblas_dgemm(
			CblasRowMajor, 
			CblasTrans, 
			CblasNoTrans, 
			1, 
			1, 
			numInputNeurons, 
			1.0, 	
			outputs,
			1, 
			weights + x, 
			1, 
			1.0, 
			&out, 
			1
		);
		outputs[i] = sigmoid(out + biases[i]);
		//std::cout << outputs[i] << " ";
	}

	int numInputConnections = numInputNeurons * numLayer1Neurons;
	for(int i = numInputNeurons+numLayer1Neurons; i<numInputNeurons+numLayer1Neurons+numLayer2Neurons; i++) {
		double out = 0;
		int x = numInputConnections + (i-numInputNeurons-numLayer1Neurons)*numLayer1Neurons;
		cblas_dgemm(
			CblasRowMajor,
			CblasTrans,
			CblasNoTrans,
			1,
			1,
			numLayer1Neurons,
			1.0,
			outputs + numInputNeurons,
			1,
			weights + x,
			1,
			1.0,
			&out,
			1
		);
		outputs[i] = sigmoid(out + biases[i]);
	}

	int numC = numInputConnections + (numLayer1Neurons*numLayer2Neurons);
	int g = numInputNeurons + numLayer1Neurons + numLayer2Neurons;
	for(int i = g; i<totalNeurons; i++) {
		double out = 0;
		int x = numC + (i-g)*numLayer2Neurons;
		cblas_dgemm(
			CblasRowMajor,
			CblasTrans,
			CblasNoTrans,
			1,
			1,
			numLayer2Neurons,
			1.0,
			outputs + numInputNeurons + numLayer1Neurons,
			1,
			weights + x,
			1,
			1.0,
			&out,
			1
		);
		outputs[i] = sigmoid(out + biases[i]);
	}
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

