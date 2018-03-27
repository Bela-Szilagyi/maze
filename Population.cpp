#include <iostream>
#include "Population.h"

Population::Population(int populationSize, bool initialise) : populationSize(populationSize)
{
	if (initialise)
	{
		for (int i = 0; i < size(); ++i)
		{
			std::shared_ptr<Individual> newIndividual = std::make_shared<Individual>(4);
			//newIndividual->generateIndividual(4);
			saveIndividual(newIndividual);
		}
		Individual::setSolution("1111");
	}
}

Population::~Population()
{
}

void Population::saveIndividual(std::shared_ptr<Individual> individual)
{
	individuals.push_back(individual);
	std::cout << individual->to_string_() << std::endl;
}

std::shared_ptr<Individual> Population::getFittest()
{
	std::shared_ptr<Individual> fittest = individuals[0];
	for (int i = 0; i < size(); ++i) {
		if (fittest->getFitness() <= getIndividual(i)->getFitness()) 
		{
			fittest = getIndividual(i);
		}
	}
	return fittest;
}