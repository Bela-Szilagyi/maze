#pragma once

#include "Population.h"
#include "Individual.h"

class Algorithm
{
public:
	Algorithm();
	~Algorithm();

	static Population evolvePopulation(Population &population);
private:
	static double uniformRate;
	static double mutationRate;
	static int tournamentSize;
	static bool elitism;

	static std::shared_ptr<Individual> crossover(std::shared_ptr<Individual> individual1, std::shared_ptr<Individual> individual2);
	static void mutate(std::shared_ptr<Individual> individual);
	static Individual tournamentSelection(const Population &population);
};

