#include "GeneticAlgorithm.h"




GeneticAlgorithm::GeneticAlgorithm()
{
	std::cout << "GA is created" << std::endl;
}


GeneticAlgorithm::~GeneticAlgorithm()
{
}

std::vector< std::shared_ptr<Cell> > GeneticAlgorithm::solveMaze(int populationSize, int genesSize, Maze &maze)
{
	std::string solution = "111111111111111111111111";
	std::vector< std::shared_ptr<Cell> > path{};
	//Population population(populationSize, true, genesSize, solution);
	std::shared_ptr<Population> population = std::make_shared<Population>(populationSize, true, maze, genesSize);
	std::cout << "Fittest: ";
	std::string genes = population->getFittest(maze)->to_string_();
	std::cout << genes << std::endl;
	/*std::cout << "The population: " << std::endl;
	for (int i = 0; i < populationSize; ++i)
	{
		std::cout << population->getIndividual(i)->to_string_() << std::endl;
	}*/

	int generationCnt = 0;
	int conversionCount = 0;
	double oldFitness = 100;
	// TODO !!!!!
	//while (population->getFittest(maze)->getFitness(maze) < Individual::getMaxFitness()) {
	while (population->getFittest(maze)->getFitness(maze) < 100) {
		++generationCnt; ++conversionCount;
		if(oldFitness < population->getFittest(maze)->getFitness(maze)) conversionCount = 0;
		//std::cout << "OF: " << oldFitness << ", NF: " << population->getFittest(maze)->getFitness(maze);
		std::cout << " Generation: " << generationCnt << ", not converged rounds: " << conversionCount << ", Fittest: " << population->getFittest(maze)->getFitness(maze) << std::endl << ", genes of the fittest: " << population->getFittest(maze)->to_string_h() << std::endl;
		//std::cout << " distfromgoal: " << population->getFittest(maze)->minDistanceFromGoal << " ";
		oldFitness = population->getFittest(maze)->getFitness(maze);
		population = Algorithm::evolvePopulation(population, maze);
		//if (conversionCount == 2000) {
		//	population = std::make_shared<Population>(population->size(), true, maze, genesSize);
		//	//population = newPopulation;
		//	conversionCount = 0;
		//}
		
		//if (generationCnt == 4000) break;
		
	}
	std::cout << std::endl;
	std::cout << "Solution found!" << std::endl;
	std::cout << "Generation: " << generationCnt << std::endl;
	std::cout << "Genes of the fittest: " << std::endl << population->getFittest(maze)->to_string_() << std::endl;
	population = Algorithm::evolvePopulation(population, maze);
	genes = population->getFittest(maze)->to_string_();
	//std::cout << "Fittest after one cycle: ";
	//std::cout << genes << std::endl;
	
	for(int i = 0; i < population->size(); ++i)
	{
		std::cout << population->getIndividual(i)->to_string_h() << std::endl;
	}

	// "export" the path of the fittest
	path.push_back(maze.cells[0]);
	int indexOfLastElement = maze.width * maze.height - 1;
	std::shared_ptr<Cell> goal = maze.cells[indexOfLastElement];
	std::shared_ptr<Individual> fittest = population->getFittest(maze);
	std::shared_ptr<Cell> currentCell = maze.cells[0];
	std::string currDir;
	for (int i = 0; i < fittest->size(); i = i + 2)
	{
		currDir = std::to_string(fittest->getGene(i)) + std::to_string(fittest->getGene(i + 1));
		if (currDir == "00" && !currentCell->nWall)
		{
			path.push_back(currentCell->nNeighbor);
			currentCell = currentCell->nNeighbor;
		}
		else if (currDir == "01" && !currentCell->wWall)
		{
			path.push_back(currentCell->wNeighbor);
			currentCell = currentCell->wNeighbor;
		}
		else if (currDir == "10" && !currentCell->sWall)
		{
			path.push_back(currentCell->sNeighbor);
			currentCell = currentCell->sNeighbor;
		}
		else if (currDir == "11" && !currentCell->eWall)
		{
			path.push_back(currentCell->eNeighbor);
			currentCell = currentCell->eNeighbor;
		}
		else break;
		if (currentCell == goal) break;
	}

	return path;



	//std::cout << "Target chromosome: " << solution << std::endl;

	//int generationCnt = 0;
	/*while (population->getFittest()->getFitness() < Individual::getMaxFitness()) {
		++generationCnt;
		std::cout << "Generation: " << generationCnt << ", Fittest: " << population->getFittest()->getFitness() << ", genes of the fittest: " << population->getFittest()->to_string_() << std::endl;
		population = Algorithm::evolvePopulation(population, maze);
	}
	std::cout << std::endl;
	std::cout << "Solution found!" << std::endl;
	std::cout << "Generation: " << generationCnt << std::endl;
	std::cout << "Genes of the fittest: " << population->getFittest()->to_string_() << std::endl;
	population = Algorithm::evolvePopulation(population);
	genes = population->getFittest()->to_string_();
	std::cout << "Fittest after one cycle: ";
	std::cout << genes << std::endl;
	*/
	//auto pop = population.
}
