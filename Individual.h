#pragma once

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <memory>
//#include "FitnessCalc.h"

class Individual
{
public:
	Individual(int geneLength);
	~Individual();
	
	void generateIndividual();
	int getFitness();
	//static void setDefaultGeneLength(int length);
	int size() { return genes.size(); }
	int getGene(int index) { return genes[index]; }
	void setGene(int index, int value);
	std::string to_string_();

	static std::vector<int> solution;
	static void setSolution(std::vector<int> newSolution);
	static void setSolution(std::string newSolution);
	static int getFitness(Individual individual);
	static int getMaxFitness();

private:
	//static int defaultGeneLength;
	int fitness = 0;
	int geneLength;
	//int genes[defaultGeneLength];
	std::vector<int> genes;
};
