#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "Evolution.h"
#include "NeuralNetwork.h"
#include "Evaluation.h"
#include "StatsFile.h"
#include "cuEval.h"

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
}


void Evolution::Output() {	
	std::cout << "\tBest Performer:\t  " << evaluations[0]->getPercentCorrect() << "\n";
	std::cout << "\tQ3:\t\t  " << evaluations[populationSize / 4]->getPercentCorrect() << "\n";
	std::cout << "\tMedian Performer: " << evaluations[populationSize / 2]->getPercentCorrect() << "\n";
	std::cout << "\tQ1:\t\t  " << evaluations[3 * (populationSize / 4)]->getPercentCorrect() << "\n";
	//Dump();

	
}

void Evolution::Dump() {
	for(int x =0; x < populationSize; x++) {
		std::cout << evaluations[x]->getPercentCorrect() << "  ";
	}
}

bool Evolution::CompareEvaluationPercent(const std::unique_ptr<Evaluation> &e1,
	const std::unique_ptr<Evaluation> &e2){
	return (e1->getPercentCorrect() > e2->getPercentCorrect());
}


void Evolution::Elimination()
{
	eliminated.clear();
	
	for(unsigned i = populationSize/4; i < evaluations.size(); i++)
	{
		Evaluation *evaluation = evaluations[i].get();
		double eliminationProbability = (1.0 / populationSize) * (i - populationSize/4);
		double num = (1.0 * rand() / RAND_MAX);
		if(num < eliminationProbability) {
			eliminated.insert(evaluation->id);
			individuals[evaluation->id]->Initialize();
		}
	}
}



void Evolution::CrossOver()
{
	std::cout << "Eliminated " << eliminated.size() << " individuals" << std::endl;
	int remaining = populationSize - eliminated.size();
	int possibleCrossover = (remaining + 1) * remaining / 2;
	
	double probabilityDecrease = 0.00055; //FIXME

	std::vector<std::unique_ptr<NeuralNetwork>> newIndividuals;


	for(int i = 0; i < 2; i++){
		Evaluation* evaluation = evaluations[i].get();
		int id = evaluation->id;
		NeuralNetwork * nn = individuals[id].get();

		auto newNN = nn->Clone();
		newIndividuals.push_back(std::move(newNN));
	}

	int count = 2;
	double probability = 0.7;
	for(unsigned i = 0; i < evaluations.size(); i++){
		Evaluation *evaluation = evaluations[i].get();
		int id = evaluation->id;

		if(count >= populationSize) break;

		if(eliminated.find(id) != eliminated.end()) continue;

		for(unsigned j = 0; j < evaluations.size(); j++){
			Evaluation * evaluation2 = evaluations[j].get();
			int id2 = evaluation2->id;

			if(id==id2) continue;
			if(eliminated.find(id2) != eliminated.end()) continue;

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



// TODO smarter mutations
void Evolution::Mutation()
{
	int count1 = 0;
	double mutationProbability = 0.039;
	double mutationStrength = 0.5;
	for(auto &nn : individuals){
		for(auto x: nn->biases){
			double num = 1.0 * rand() / RAND_MAX;
			if(num < mutationProbability){
				// FIXME
				count1++;
				double change = mutationStrength * (2.0 * rand() / RAND_MAX - 1.0);
				x += x * change;
			}
		}

		for(auto x: nn->weights){
			double num = 1.0 * rand() / RAND_MAX;
			if(num < mutationProbability){
				// FIXME
				count1++;
				double change = mutationStrength * (2.0 * rand() / RAND_MAX - 1.0);
				x += x * change; 
			}
		}
	}

	std::cout << count1 << " mutations introduced" << std::endl;
}

void Evolution::Run()
{
	RandomizePopulation();
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);

	StatsFile file("output-1.csv");
	for(int i = 0; i < maxGenerations; i++){
		std::cout << "Generation: " << i << "\n";
		EvaluateAll();
		Sort();
		if(i % 40 == 0) {
			evaluations[0]->EvaluateFull();
			std::cout << "Best Performer total performance: " << evaluations[0]->getPercentCorrectFull() << "\n";
		}
		Output();
		file.WriteGeneration(i, evaluations[0]->getPercentCorrect(),
					evaluations[0]->getPercentCorrectFull());

		Elimination();
		CrossOver();
		Mutation();

		std::cout << std::endl;
	}
}


void Evolution::EvaluateAll()
{

	// copy all data to global memory:
	//   -- weights/biases for all individuals
	//   -- a test set subset matrix
	

	// invoke a kernel call for evaluations (launches sub-kernels,
	// each on different streams (only dependencies are within one eval)
	// parrallizes launch of individual evaluations
	

	// cudaMemcpyDeviceToHost Results
	// consider parallelizing mutation/crossover

	evaluations.clear();
	// TODO	add cuda call to parallelize evaluations
	// -- each evauluation will have 3 cuda calls for feed forward
	for(int i = 0; i < populationSize; i++){
		auto evaluation = std::unique_ptr<Evaluation>(new Evaluation);
		evaluation->id = i;
	
		evaluation->network = individuals[i].get();
			
		evaluation->Evaluate();

	
		evaluations.push_back(std::move(evaluation));
	}
}
