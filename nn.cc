

#include <iostream>
#include "NeuralNetwork.h"


int main(void)
{
	NeuralNetwork* n = new NeuralNetwork();
	n->Initialize();

	for(int i = 0; i < n->neurons.size(); i++)
	{
		std::cout << n->neurons[i]->bias << " ";
	}
}

