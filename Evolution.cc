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


// TODO eliminate based on fitness
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



// TODO crossover based on fitness
// FIXME entire crossover function
// this was taken directly from Hetero-Mark simply to have a working function
void Evolution::CrossOver()
{

	int remaining = populationSize - eliminated.size();
	int possibleCrossover = (remaining + 1) * remaining / 2;
	
	double probabilityDecrease = 0.002; //FIXME

	std::vector<std::unique_ptr<NeuralNetwork>> newIndividuals;


	// clone first two?
	for(int i = 0; i < 2; i++){
		Evaluation* evaluation = evaluations[i].get();
		int id = evaluation->id;
		NeuralNetwork * nn = individuals[id].get();

		auto newNN = nn->Clone();
		newIndividuals.push_back(std::move(newNN));
	}

	int count = 2;
	double probability = 0.6;
	for(unsigned i = 0; i < evaluations.size(); i++){
		Evaluation *evaluation = evaluations[i].get();
		int id = evaluation->id;

		if(count >= populationSize) break;

		if(eliminated.find(id) != eliminated.end()) continue; // FIXME ?

		for(unsigned j = 0; j < evaluations.size(); j++){
			Evaluation * evaluation2 = evaluations[j].get();
			int id2 = evaluation2->id;

			if(id==id2) continue;
			if(eliminated.find(id2) != eliminated.end()) continue; // FIXME ?

			if( count >= populationSize) break;

			double num = 1.0 * rand() / RAND_MAX;

			if(num < probability) {
				count++;
				std::unique_ptr<NeuralNetwork> n = individuals[i]->Crossover(individuals[id2].get());

				newIndividuals.push_back(std::move(n));
			}

			probability -= probabilityDecrease;
		}
	}

	std::cout << "Created " << newIndividuals.size() << " new individuals by crossover\n";

	// if not created by crossover, add entirely new individuals to complete population
	while(newIndividuals.size() < (unsigned) populationSize){
		std::unique_ptr<NeuralNetwork> nn(new NeuralNetwork());
		nn->Initialize();
		newIndividuals.push_back(std::move(nn));
	}

	for(int i = 0; i < populationSize; i++){
		individuals[i] = std::move(newIndividuals[i]);
	}
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
