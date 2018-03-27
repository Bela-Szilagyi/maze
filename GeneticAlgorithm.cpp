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
	std::cout << "Fittest: ";
	std::string genes = population.getFittest()->to_string_();
	std::cout << genes << std::endl;
	//auto pop = population.
}
