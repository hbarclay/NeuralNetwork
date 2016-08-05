
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
		Evaluation::labels = Evaluation::readMnistLabels("/home/harrison/git-repos/NeuralNetworkCPU/datasets/MNIST/train-labels-idx1-ubyte");
		Evaluation::images = Evaluation::readMnistImages("/home/harrison/git-repos/NeuralNetworkCPU/datasets/MNIST/train-images-idx3-ubyte");

		Evolution* evolution = new Evolution();
		evolution->setMaxGenerations(std::stoi(args[1]));
		evolution->setPopulationSize(std::stoi(args[2]));

		evolution->Run();	
	}

//	Evaluation* e = new Evaluation();
//	e->Test();

	return 0;
}

