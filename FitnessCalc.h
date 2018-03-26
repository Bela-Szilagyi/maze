#pragma once

#include <vector>
#include <memory>
#include "Individual.h"

class FitnessCalc
{
public:
	FitnessCalc();
	~FitnessCalc();

	static std::vector<int> solution;

	static void setSolution(std::vector<int> newSolution);
	static void setSolution(std::string newSolution);
	static int getFitness(std::shared_ptr<Individual> individual);
	static int getMaxFitness();
};

