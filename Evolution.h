

#ifndef SRC_EVOLUTION
#define SRC_EVOLUTION

#include <set>
#include <cstdlib>
#include "NeuralNetwork.h"
#include "Evaluation.h"

class Evolution {
	
	int maxGenerations = 100;
	int populationSize;

	std::vector<std::unique_ptr<Evaluation>> evaluations;
	std::vector<std::unique_ptr<NeuralNetwork>> individuals;
	std::set<int> eliminated;

	void RandomizePopulation();
	void Sort();
	void Elimination();
	void CrossOver();
	void Mutation();
	void EvaluateAll();

	static bool CompareEvaluationPercent(const std::unique_ptr<Evaluation> &e1,
		const std::unique_ptr<Evaluation> &e2);

public:
	void Run();	
	void Output();	
	void Dump();
	void CountIdentical();
	
	void setPopulationSize(int pop){
		populationSize = pop;
	}

	
	void setMaxGenerations(int g) {
		maxGenerations = g;
	}
};

#endif
