#include "Evaluation.h"
#include "NeuralNetwork.h"
#include <cstdlib>
#include <random>
#include <iostream>

void Evaluation::Evaluate()
{
//	network->Dump();	
	createTestSet();	
	int correct = 0;
	for(int i = 0; i < testSetSize; i++){	
		network->setNeuronOutput(0, val1[i]);
		network->setNeuronOutput(1, val2[i]);
		network->setNeuronOutput(2, val3[i]);
		
		network->feedForward();
		
		std::cout << val1[i] + val2[i] + val3[i] << ":\t" << network->getOutput(NeuralNetwork::totalNeurons-1) << "\n";	
		if(((int)network->getOutput(NeuralNetwork::totalNeurons-1)) == val1[i] + val2[i] + val3[i])
			correct++;

		
	}
	percentCorrect = (double) correct / (double) testSetSize;
		
}


void Evaluation::setInputNeurons(){

}


void Evaluation::createTestSet(){
	for(int i = 0; i < 30000; i++){
		val1[i] = rand() % 10 + 1;
		val2[i] = rand() % 10 + 1;
		val3[i] = rand() % 10 + 1;
	}
}
