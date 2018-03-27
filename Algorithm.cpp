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


	return population;
}

std::shared_ptr<Individual> Algorithm::crossover(std::shared_ptr<Individual> individual1, std::shared_ptr<Individual> individual2)
{
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

std::shared_ptr<Individual> Algorithm::tournamentSelection(Population & population)
{
	Population tournament(tournamentSize, false);
	//std::cout << "They are going to a tournament: " << std::endl;
	for (int i = 0; i < tournamentSize; ++i)
	{
		int randomId = rand() % population.size();
		//std::cout << population.getIndividual(randomId)->to_string_() << std::endl;
		tournament.saveIndividual(population.getIndividual(randomId));
	}
	//std::cout << "And the winner is: " << tournament.getFittest()->to_string_() << std::endl;
	return tournament.getFittest();
}
