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
	//Population population(populationSize, true, genesSize, solution);
	std::shared_ptr<Population> population = std::make_shared<Population>(populationSize, true, genesSize, solution);
	//std::cout << "Fittest: ";
	//std::string genes = population->getFittest()->to_string_();
	//std::cout << genes << std::endl;

	std::cout << "Target chromosome: " << solution << std::endl;

	int generationCnt = 0;
	while (population->getFittest()->getFitness() < Individual::getMaxFitness()) {
		++generationCnt;
		std::cout << "Generation: " << generationCnt << ", Fittest: " << population->getFittest()->getFitness() << ", genes of the fittest: " << population->getFittest()->to_string_() << std::endl;
		population = Algorithm::evolvePopulation(population);
	}
	std::cout << std::endl;
	std::cout << "Solution found!" << std::endl;
	std::cout << "Generation: " << generationCnt << std::endl;
	std::cout << "Genes of the fittest: " << population->getFittest()->to_string_() << std::endl;
	/*population = Algorithm::evolvePopulation(population);
	genes = population->getFittest()->to_string_();
	std::cout << "Fittest after one cycle: ";
	std::cout << genes << std::endl;*/

	//auto pop = population.
}
