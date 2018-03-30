#include <iostream>
#include "Population.h"


Population::Population(int populationSize, bool initialise, Maze &maze, int genesSize) : populationSize(populationSize), maze(maze)
{
	if (initialise)
	{
		//Individual::setSolution(solution);
		//individuals.clear();
		for (int i = 0; i < size(); ++i)
		{
			std::shared_ptr<Individual> newIndividual = std::make_shared<Individual>(genesSize);
			//newIndividual->generateIndividual(4);
			saveIndividual(newIndividual);
		}
	}
}

Population::~Population()
{
}

void Population::saveIndividual(std::shared_ptr<Individual> individual)
{
	individuals.push_back(individual);
	//std::cout << individual->to_string_() << std::endl;
}

std::shared_ptr<Individual> Population::getFittest(Maze &maze)
{
	std::shared_ptr<Individual> fittest = individuals[0];
	for (int i = 0; i < size(); ++i) {
		if (fittest->getFitness(maze) <= getIndividual(i)->getFitness(maze)) 
		{
			fittest = getIndividual(i);
		}
	}
	return fittest;
}