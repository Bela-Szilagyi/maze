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
	std::string genes = population.getFittest()->to_string_();
	std::cout << genes << std::endl;
}
