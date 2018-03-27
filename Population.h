#pragma once

#include <memory>
#include <vector>
#include "Individual.h"

class Population
{
public:
	Population(int populationSize, bool initialise, int genesSize, std::string solution);
	~Population();

	int size() { return populationSize; }
	void saveIndividual(std::shared_ptr<Individual> individual);
	std::shared_ptr<Individual> getIndividual(int index) { return individuals[index]; }
	std::shared_ptr<Individual> getFittest();

private:
	std::vector< std::shared_ptr<Individual> > individuals;
	int populationSize;
};

