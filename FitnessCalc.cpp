#include "FitnessCalc.h"


std::vector<int> FitnessCalc::solution;

FitnessCalc::FitnessCalc()
{
}


FitnessCalc::~FitnessCalc()
{
}

void FitnessCalc::setSolution(std::vector<int> newSolution)
{
	solution = newSolution;
}

void FitnessCalc::setSolution(std::string newSolution)
{
	for (int i = 0; i < newSolution.size(); ++i)
	{
		solution[i] = newSolution[i] == '0' ? 0 : 1;
	}
}

int FitnessCalc::getFitness(std::shared_ptr<Individual> individual)
{
	int fitness = 0;
	for (int i = 0; i < individual->size(); ++i)
	{
		if (individual->getGene(i) == solution[i])
		{
			fitness++;
		}
	}
	return fitness;
}

int FitnessCalc::getMaxFitness()
{
	return solution.size();
}