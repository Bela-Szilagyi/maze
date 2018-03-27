#pragma once

#include <iostream>
#include "Population.h"
#include "Algorithm.h"

class GeneticAlgorithm
{
public:
	GeneticAlgorithm();
	~GeneticAlgorithm();
	void run(int populationSize, int genesSize, std::string solution);
};

