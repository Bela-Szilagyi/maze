#include "Individual.h"

//int Individual::defaultGeneLength = 64;
std::vector<int> Individual::solution;


Individual::Individual(int geneLength) : geneLength(geneLength)
{
	generateIndividual();
}


Individual::~Individual()
{
}

void Individual::generateIndividual()
{
	for (int i = 0; i < geneLength; ++i)
	{
		int gene = rand() % 2;
		genes.push_back(gene);
	}
}

int Individual::getFitness()
{
	if (fitness == 0)
	{
		fitness = getFitness(*this);
	}
	return fitness;
}

void Individual::setGene(int index, int value)
{
	genes[index] = value;
	fitness = 0;
}

std::string Individual::to_string_()
{
	std::string result = "";
	for (int i = 0; i < size(); ++i)
	{
		result += std::to_string(genes[i]);
	}
	return result;
}

void Individual::setSolution(std::vector<int> newSolution)
{
	solution = newSolution;
}

void Individual::setSolution(std::string newSolution)
{
	for (int i = 0; i < newSolution.size(); ++i)
	{
		solution.push_back(newSolution[i] == '0' ? 0 : 1);
	}
}

int Individual::getFitness(Individual individual)
{
	int fitness = 0;
	for (int i = 0; i < individual.size(); ++i)
	{
		if (individual.getGene(i) == solution[i])
		{
			fitness++;
		}
	}
	return fitness;
}

int Individual::getMaxFitness()
{
	return solution.size();
}