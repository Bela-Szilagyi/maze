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
	void run(int populationSize, int genesSize, Maze &maze);
};

