#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <thread>
#include "Evolution.h"
#include "NeuralNetwork.h"
#include "Evaluation.h"

void Evolution::RandomizePopulation()
{


}

void Evolution::Sort()
{

}

void Evolution::Elimination()
{

}

void Evolution::CrossOver()
{

}

void Evolution::Mutation()
{

}

void Evolution::Run()
{

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
