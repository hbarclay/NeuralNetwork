
#include <string>
#include <iostream>
#include "NeuralNetwork.h"
#include "Evolution.h"

int main(int argc, char *args[])
{
	if(argc != 3){
		std::cout << "usage: " << args[0] <<  " <maxGenerations> <PopulationSize>";
	}
	else{
		Evolution* evolution = new Evolution();
		evolution->setMaxGenerations(std::stoi(args[1]));
		evolution->setPopulationSize(std::stoi(args[2]));

		evolution->Run();	
	}

	return 0;
}

