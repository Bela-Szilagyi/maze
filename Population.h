#pragma once
#include <memory>
#include <vector>
#include "Individual.h"

class Population
{
public:
	Population(int populationSize, bool initialise);
	~Population();

	int size() { return populationSize; }
private:
	std::vector< std::shared_ptr<Individual> > individuals;
	int populationSize;
};

