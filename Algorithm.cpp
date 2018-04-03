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

std::shared_ptr<Population>  Algorithm::evolvePopulation(std::shared_ptr<Population> population, Maze &maze)
{
	//std::cout << "Evolving population...." << std::endl;
	// TODO: implement this function

	std::shared_ptr<Population> newPopulation = std::make_shared<Population>(population->size(), false, maze);

	if (elitism)
	{
		newPopulation->saveIndividual(population->getFittest(maze));
	}

	int elitismOffset;
	if (elitism) {
		elitismOffset = 1;
	}
	else {
		elitismOffset = 0;
	}

	std::shared_ptr<Individual> copyOfFittest = std::make_shared<Individual>(population->getFittest(maze)->size());
	std::string genesOfFittest = population->getFittest(maze)->getGenes();
	//std::string genesOfFittest = "1111111111";
	for (int i = 0; i < genesOfFittest.size(); ++i)
	{
		copyOfFittest->setGene(i, (int)genesOfFittest[i] - '0');
	}
	newPopulation->saveIndividual(copyOfFittest);

	//std::cout << copyOfFittest->getGenes() << std::endl;

	for (int i = elitismOffset+1; i < population->size(); ++i) {
		//std::shared_ptr<Individual> indiv1 = tournamentSelection(population, maze);
		std::shared_ptr<Individual> indiv1 = i < population->size() / 2 ? population->getFittest(maze) : copyOfFittest;
		//std::shared_ptr<Individual> indiv1 = population->getFittest(maze);
		std::shared_ptr<Individual> indiv2 = tournamentSelection(population, maze);
		std::shared_ptr<Individual> newIndiv = crossover(indiv1, indiv2);
		newPopulation->saveIndividual(newIndiv);
	}

	for (int i = elitismOffset; i < newPopulation->size(); ++i) {
		mutate(newPopulation->getIndividual(i));
	}
	// for testing mutation()
	//std::shared_ptr<Individual> indi = population.getFittest();
	//mutate(indi);

	//for testing crossover()
	/*std::shared_ptr<Individual> indi = population.getFittest();
	std::shared_ptr<Individual> indi2 = std::make_shared<Individual>(10);
	std::shared_ptr<Individual> crossedOver = crossover(indi, indi2);
	std::cout << "Crossover partner 1: " << indi->to_string_() << " crossover partner 2: " << indi2->to_string_() << std::endl;
	std::cout << "Crossed over individual: " << crossedOver->to_string_() << std::endl;
	*/
	
	// for testing tournamentSelection()
	//std::shared_ptr<Individual> TSTest = tournamentSelection(population);
	//std::cout << "Tournament winner: " << TSTest->to_string_() << std::endl;


	return newPopulation;
}

std::shared_ptr<Individual> Algorithm::crossover(std::shared_ptr<Individual> individual1, std::shared_ptr<Individual> individual2)
{
	std::shared_ptr<Individual> result = std::make_shared<Individual>(individual1->size());
	int randomNumber;
	for (int i = 0; i < individual1->size(); i = i + 2)
	{
		randomNumber = rand() % 100 + 1;
		if (randomNumber <= (int)(uniformRate * 10))
		{
			result->setGene(i, individual1->getGene(i));
			result->setGene(i + 1, individual1->getGene(i + 1));
		} 
		else
		{
			result->setGene(i, individual2->getGene(i));
			result->setGene(i + 1, individual2->getGene(i + 1));
		}
	}
	return result;
}

void Algorithm::mutate(std::shared_ptr<Individual> individual)
{
	int randomNumber;
	/*for (int i = 0; i < individual->size(); ++i)
	{
		randomNumber = rand() % 1000 + 1;
		if (randomNumber <= (int) (mutationRate * 1000)) individual->setGene(i, rand() % 2);
	}*/
	for (int i = 0; i < individual->size(); i = i + 2)
	{
		randomNumber = rand() % 1000 + 1;
		if (randomNumber <= (int)(mutationRate * 1000))
		{
			individual->setGene(i, rand() % 2);
			individual->setGene(i + 1, rand() % 2);
		}
	}
}

std::shared_ptr<Individual> Algorithm::tournamentSelection(std::shared_ptr<Population> population, Maze &maze)
{
	Population tournament(tournamentSize, false, maze);
	//std::cout << "They are going to a tournament: " << std::endl;
	for (int i = 0; i < tournamentSize; ++i)
	{
		int randomId = rand() % population->size();
		//std::cout << population.getIndividual(randomId)->to_string_() << std::endl;
		tournament.saveIndividual(population->getIndividual(randomId));
	}
	//std::cout << "And the winner is: " << tournament.getFittest()->to_string_() << std::endl;
	return tournament.getFittest(maze);
}
