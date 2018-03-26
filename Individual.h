#pragma once

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>

class Individual
{
public:
	Individual();
	~Individual();
	
	void generateIndividual(int geneLenght);
	int getFitness();
	//static void setDefaultGeneLength(int length);
	int size() { return genes.size(); }
	int getGene(int index) { return genes[index]; }
	void setGene(int index, int value);
	std::string to_string_();
private:
	//static int defaultGeneLength;
	int fitness = 0;
	//int genes[defaultGeneLength];
	std::vector<int> genes;
};
