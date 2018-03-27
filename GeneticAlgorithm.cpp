#include "GeneticAlgorithm.h"




GeneticAlgorithm::GeneticAlgorithm()
{
	std::cout << "GA is created" << std::endl;
}


GeneticAlgorithm::~GeneticAlgorithm()
{
}

void GeneticAlgorithm::run(int populationSize, int genesSize, std::string solution)
{
	Population population(populationSize, true, genesSize, solution);
	std::cout << "Fittest: ";
	std::string genes = population.getFittest()->to_string_();
	std::cout << genes << std::endl;

	population = Algorithm::evolvePopulation(population);
	genes = population.getFittest()->to_string_();
	std::cout << "Fittest after one cycle: ";
	std::cout << genes << std::endl;

	//auto pop = population.
}
