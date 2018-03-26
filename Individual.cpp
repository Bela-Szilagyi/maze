#include "Individual.h"

//int Individual::defaultGeneLength = 64;
std::vector<int> Individual::solution;


Individual::Individual()
{
	//temp solution
	for (int i = 0; i < 64; ++i)
	{
		solution.push_back(0);
	}
}


Individual::~Individual()
{
}

void Individual::generateIndividual(int geneLenght)
{
	for (int i = 0; i < geneLenght; ++i)
	{
		int gene = rand() % 2;
		genes.push_back(gene);
	}
	//fitness = 10;
}

int Individual::getFitness()
{
	// TODO: implement this fuction:
	if (fitness == 0)
	{
		// if this is uncommented, the program will crash:
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

/*void Individual::setDefaultGeneLength(int length)
{
	defaultGeneLength = length;
}*/

void Individual::setSolution(std::vector<int> newSolution)
{
	solution = newSolution;
}

void Individual::setSolution(std::string newSolution)
{
	for (int i = 0; i < newSolution.size(); ++i)
	{
		solution[i] = newSolution[i] == '0' ? 0 : 1;
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
