#include "Algorithm.h"

double Algorithm::uniformRate = 0.50;
double Algorithm::mutationRate = 0.015;
int Algorithm::tournamentSize = 5;
bool Algorithm::elitism = true;

Algorithm::Algorithm()
{
}


Algorithm::~Algorithm()
{
}

Population Algorithm::evolvePopulation(Population & population)
{
	//std::cout << "Evolving population...." << std::endl;
	// TODO: implement this function

	// for testing mutation()
	//std::shared_ptr<Individual> indi = population.getFittest();
	//mutate(indi);

	return population;
}

std::shared_ptr<Individual> Algorithm::crossover(std::shared_ptr<Individual> individual1, std::shared_ptr<Individual> individual2)
{
	// TODO: implement this function
	std::shared_ptr<Individual> result = std::make_shared<Individual>(individual1->size());
	int randomNumber;
	for (int i = 0; i < individual1->size(); ++i)
	{
		randomNumber = rand() % 100 + 1;
		if (randomNumber <= (int)(uniformRate * 10))
		{
			result->setGene(i, individual1->getGene(i));
		} 
		else
		{
			result->setGene(i, individual2->getGene(i));
		}
	}
	return result;
}

void Algorithm::mutate(std::shared_ptr<Individual> individual)
{
	int randomNumber;
	for (int i = 0; i < individual->size(); ++i)
	{
		randomNumber = rand() % 1000 + 1;
		if (randomNumber <= (int) (mutationRate * 1000)) individual->setGene(i, rand() % 2);
	}
}

Individual Algorithm::tournamentSelection(const Population & population)
{
	// TODO: implement this function
	return *(new Individual(0));
}
