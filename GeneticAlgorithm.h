#pragma once

#include <iostream>
#include "Population.h"
#include "Algorithm.h"
#include "Maze.h"

class GeneticAlgorithm
{
public:
	GeneticAlgorithm();
	~GeneticAlgorithm();
	std::vector< std::shared_ptr<Cell> > solveMaze(int populationSize, int genesSize, Maze &maze);
};

