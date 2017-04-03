#include <string>
#include <iostream>

#include "NeuralNetwork.h"
#include "Evolution.h"
#include "Evaluation.h"

int main(int argc, char *args[])
{
	if(argc != 3){
		std::cout << "usage: " << args[0] <<  " <maxGenerations> <PopulationSize>";
	}
	else{
		Evaluation::labels = Evaluation::readMnistLabels("./datasets/MNIST/train-labels-idx1-ubyte");
		Evaluation::images = Evaluation::readMnistImages("./datasets/MNIST/train-images-idx3-ubyte");

		Evolution* evolution = new Evolution();
		evolution->setMaxGenerations(std::stoi(args[1]));
		evolution->setPopulationSize(std::stoi(args[2]));

		evolution->Run();	
	}

	return 0;
}

