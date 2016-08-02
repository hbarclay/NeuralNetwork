

#ifndef SRC_EVOLUTION
#define SRC_EVOLUTION

#include <set>
#include <cstdlib>
#include "NeuralNetwork.h"
#include "Evaluation.h"

class Evolution {
	
	int maxGenerations;
	int populationSize;

	std::vector<std::unique_ptr<Evaluation>> evaluations;
	std::vector<std::unique_ptr<NeuralNetwork>> individuals;
	std::set<int> eliminated;

	void RandomizePopulation();
	void Sort();
	void Elimination();
	void CrossOver();
	void Mutation();

public:
	void Run();	
	

	void setPopulationSize(int pop){
		populationSize = pop;
	}

};

#endif
