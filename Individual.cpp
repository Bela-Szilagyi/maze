#include "Individual.h"

//int Individual::defaultGeneLength = 64;
std::vector<int> Individual::solution;


Individual::Individual(int geneLength) : geneLength(geneLength)
{
	generateIndividual();
}


Individual::~Individual()
{
}

void Individual::generateIndividual()
{
	for (int i = 0; i < geneLength; ++i)
	{
		int gene = rand() % 2;
		genes.push_back(gene);
	}
}

int Individual::getFitness(Maze &maze)
{
	if (fitness == 0)
	{
		fitness = getFitness(*this, maze);
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

void Individual::setSolution(std::vector<int> newSolution)
{
	solution = newSolution;
}

void Individual::setSolution(std::string newSolution)
{
	for (int i = 0; i < newSolution.size(); ++i)
	{
		solution.push_back(newSolution[i] == '0' ? 0 : 1);
	}
}

int Individual::getFitness(Individual individual, Maze &maze)
{
	/*
	std::string cd = "11"; //Down = south
	std::shared_ptr<Cell> currentCell_ = maze.cells[0];
	currentCell_ = moveToNextCell(currentCell_, cd);
	std::cout << "value: " << currentCell_->value << std::endl;
	return 6;
	*/
	
	std::string currentDirerction;
	std::shared_ptr<Cell> currentCell = maze.cells[0];
	int indexOfLastElement = maze.width * maze.height - 1;
	std::shared_ptr<Cell> goal = maze.cells[indexOfLastElement];
	int fitness = calcFitness(currentCell, goal, 0);
	//std::cout << currentCell->value << " Fitness: " << fitness << ", genes: " << individual.getGenes() << std::endl;
	for (int i = 0; i < individual.size(); i = i + 2)
	{
		//std::cout << currentCell->value << std::endl;
		currentDirerction = std::to_string(individual.getGene(i)) + std::to_string(individual.getGene(i + 1));
		//std::cout << currentDirerction << std::endl;
		//currentCell = moveToNextCell(currentCell, currentDirerction);
		currentCell = moveToNextCell(currentCell, currentDirerction);
		if (currentCell)
		{
			// TODO: make this more intelligent:
			if (currentCell == goal) return 100;
			fitness = calcFitness(currentCell, goal, i / 2);
			//std::cout << currentCell->value << " Fitness: " << fitness << ", genes: " << individual.getGenes() <<std::endl;
		}
		else
		{
			break;
		}
	}
	
	return fitness;
}

int Individual::getMaxFitness()
{
	//return solution.size();
	return 100;
}

std::shared_ptr<Cell> Individual::moveToNextCell(std::shared_ptr<Cell> currentCell, std::string currentDirerction)
{
	std::shared_ptr<Cell> result = nullptr;
	if (currentDirerction == "00" && !currentCell->nWall) result = currentCell->nNeighbor;
	if (currentDirerction == "11" && !currentCell->eWall) result = currentCell->eNeighbor;
	if (currentDirerction == "10" && !currentCell->sWall) result = currentCell->sNeighbor;
	if (currentDirerction == "01" && !currentCell->wWall) result = currentCell->wNeighbor;
	return result;
}

int Individual::calcFitness(std::shared_ptr<Cell> currentCell, std::shared_ptr<Cell> goal, int moveCount)
{
	
	int distanceFromGoal = std::abs((int)currentCell->col - (int)goal->col) + std::abs((int)currentCell->row - (int)goal->row);
	// TODO: make this more intelligent
	return 100 - distanceFromGoal;
}
