#include "Individual.h"

//int Individual::defaultGeneLength = 64;

Individual::Individual()
{
}


Individual::~Individual()
{
}

void Individual::generateIndividual(int geneLenght)
{
	for (int i = 0; i < geneLenght; ++i)
	{
		int gene = rand() % 2;
		genes.push_back(gene);
	}
	//fitness = 10;
}

int Individual::getFitness()
{
	// TODO: implement this fuction:
	if (fitness == 0)
	{
		//fitness = FitnessCalc::getFitness(this);
	}
	return fitness;
}

void Individual::setGene(int index, int value)
{
	genes[index] = value;
	fitness = 0;
}

std::string Individual::to_string_()
{
	std::string result = "";
	for (int i = 0; i < size(); ++i)
	{
		result += std::to_string(genes[i]);
	}
	return result;
}

/*void Individual::setDefaultGeneLength(int length)
{
	defaultGeneLength = length;
}*/
