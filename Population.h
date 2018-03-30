#pragma once

#include <memory>
#include <vector>
#include "Individual.h"
#include "Maze.h"

class Population
{
public:
	Population(int populationSize, bool initialise, Maze &maze, int genesSize = 1);
	~Population();

	int size() { return populationSize; }
	void saveIndividual(std::shared_ptr<Individual> individual);
	std::shared_ptr<Individual> getIndividual(int index) { return individuals[index]; }
	std::shared_ptr<Individual> getFittest(Maze &maze);

private:
	std::vector< std::shared_ptr<Individual> > individuals;
	int populationSize;
	Maze maze;
};

