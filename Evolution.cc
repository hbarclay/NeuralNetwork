#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include "Evolution.h"
#include "NeuralNetwork.h"
#include "Evaluation.h"

void Evolution::RandomizePopulation()
{
	for(int i = 0; i < populationSize; i++){
		auto nn = std::unique_ptr<NeuralNetwork>(new NeuralNetwork());
		nn->Initialize();
		individuals.push_back(std::move(nn));
	}

}

void Evolution::Sort()
{
	std::sort(evaluations.begin(), evaluations.end(), Evolution::CompareEvaluationPercent);
	std::cout << "\tBest Performer: " << evaluations[0]->getPercentCorrect() << "\n";
	std::cout << "\tMedian Performer: " << evaluations[populationSize / 2]->getPercentCorrect() << "\n";
}

bool Evolution::CompareEvaluationPercent(const std::unique_ptr<Evaluation> &e1,
	const std::unique_ptr<Evaluation> &e2){
	return (e1->getPercentCorrect() > e2->getPercentCorrect());
}

void Evolution::Elimination()
{
	eliminated.clear();
	
	for(unsigned i = 0; i < evaluations.size(); i++)
	{
		Evaluation *evaluation = evaluations[i].get();
		double eliminationProbability = (1.0 / populationSize) * i;
		double num = (1.0 * rand() / RAND_MAX);
		if(num < eliminationProbability) {
			eliminated.insert(evaluation->id);
			individuals[evaluation->id]->Initialize();
		}
	}
}

void Evolution::CrossOver()
{
	int remaining = populationSize - eliminated.size();
	int possibleCrossover = (remaining + 1) * remaining / 2;
	

	std::vector<std::unique_ptr<NeuralNetwork>> newIndividuals;

	// TODO
}

void Evolution::Mutation()
{
	double mutationProbability = 0.1;
	double mutationStrength = 0.5;
	for(auto &nn : individuals){
		for(auto &neuron: nn->neurons){
			double num = 1.0 * rand() / RAND_MAX;
			if(num < mutationProbability){
				// FIXME
				double change = mutationStrength * (2.0 * rand() / RAND_MAX - 1.0);
				neuron->bias += neuron->bias * change;
			}
		}

		for(auto &connection: nn->connections){
			double num = 1.0 * rand() / RAND_MAX;
			if(num < mutationProbability){
				// FIXME
				double change = mutationStrength * (2.0 * rand() / RAND_MAX - 1.0);
				connection->weight += connection->weight * change; 
			}
		}
	}
}

void Evolution::Run()
{
	RandomizePopulation();
	for(int i = 0; i < maxGenerations; i++){
		std::cout << "Generation: " << i << "\n";
		EvaluateAll();
		Sort();

		Elimination();
		CrossOver();
		Mutation();
	}
}

void Evolution::EvaluateAll()
{
	evaluations.clear();
	for(int i = 0; i < populationSize; i++){
		auto evaluation = std::unique_ptr<Evaluation>(new Evaluation);
		evaluation->id = i;
	
		evaluation->network = individuals[i].get();
			
		evaluation->Evaluate();

	
		evaluations.push_back(std::move(evaluation));
		
	}
	
}
