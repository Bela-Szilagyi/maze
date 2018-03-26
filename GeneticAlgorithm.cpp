#include "GeneticAlgorithm.h"




GeneticAlgorithm::GeneticAlgorithm()
{
	std::cout << "GA is created" << std::endl;
}


GeneticAlgorithm::~GeneticAlgorithm()
{
}

void GeneticAlgorithm::run()
{
	Population population(3, true);
	/*int fitness = population.getFittest()->getFitness();
	std::cout << fitness << std::endl;*/
}
