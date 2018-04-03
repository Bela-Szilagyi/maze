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

double Individual::getFitness(Maze &maze)
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

std::string Individual::to_string_h()
{
	std::string result = "";
	std::string currentDirerction;
	for (int i = 0; i < size(); i = i + 2)
	{
		currentDirerction = std::to_string(genes[i]) + std::to_string(genes[i+1]);

		if(currentDirerction == "00") result += "N";
		else if (currentDirerction == "01") result += "W";
		else if (currentDirerction == "10") result += "S";
		else if (currentDirerction == "11") result += "E";
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

double Individual::getFitness(Individual individual, Maze &maze)
{
	/*
	std::string cd = "11"; //Down = south
	std::shared_ptr<Cell> currentCell_ = maze.cells[0];
	currentCell_ = moveToNextCell(currentCell_, cd);
	std::cout << "value: " << currentCell_->value << std::endl;
	return 6;
	*/
	std::vector<int> visitedCells;
	std::string currentDirerction;
	std::shared_ptr<Cell> currentCell = maze.cells[0];
	std::shared_ptr<Cell> start = maze.cells[0];
	visitedCells.push_back(start->value);
	int indexOfLastElement = maze.width * maze.height - 1;
	std::shared_ptr<Cell> goal = maze.cells[indexOfLastElement];
	//double fitness_ = calcFitness(currentCell, goal, start, 0, false);
	double fitness_;
	//std::cout << currentCell->value << " Fitness: " << fitness << ", genes: " << individual.getGenes() << std::endl;
	
	//std::cout << "value: " << visitedCells[0]->value << std::endl;
	bool containsVisitedCell = false;
	std::shared_ptr<Cell> lastCurrentCell = currentCell;
	int i = 0;
	for (i = 0; i < individual.size(); i = i + 2)
	{
		//std::cout << currentCell->value << std::endl;
		currentDirerction = std::to_string(individual.getGene(i)) + std::to_string(individual.getGene(i + 1));
		//std::cout << currentDirerction << std::endl;
		//currentCell = moveToNextCell(currentCell, currentDirerction);
		currentCell = moveToNextCell(currentCell, currentDirerction);
		if (currentCell)
		{
			lastCurrentCell = currentCell;
			// TODO: make this more intelligent:
			if (currentCell == goal) return 100;
			


			if (!containsVisitedCell)
			{
				for (int i = 0; i < visitedCells.size(); ++i)
				{
					//std::cout << "value: " << visitedCells[i]->value << std::endl;
					if (currentCell->value == visitedCells[i])
					{
						containsVisitedCell = true;
						break;
					}
				}
			}
			
			int distanceFromGoal = std::abs((int)currentCell->col - (int)goal->col) + std::abs((int)currentCell->row - (int)goal->row);
			//int distanceFromGoal = std::abs((int)currentCell->col);
			if (distanceFromGoal < minDistanceFromGoal)
			{
				//setMinDistanceFromGoal(individual, distanceFromGoal);
				minDistanceFromGoal = distanceFromGoal;
			}
			//else
			//{
			//distanceFromGoal = minDistanceFromGoal;
			//}


			//if (std::find(visitedCells.begin(), visitedCells.end(), currentCell->value) != visitedCells.end()) containsVisitedCell = true;
			
			visitedCells.push_back(currentCell->value);
			//fitness_ = calcFitness(currentCell, goal, start, i / 2, containsVisitedCell);
			//std::cout << currentCell->value << " Fitness: " << fitness << ", genes: " << individual.getGenes() <<std::endl;
			
			/*if (std::find(visitedCells.begin(), visitedCells.end(), currentCell) != visitedCells.end())
			{
				std::cout << currentCell->value << std::endl;
			}*/
			//std::cout << "contains visited cell: " << containsVisitedCell << " FITNESS: " << fitness << std::endl;
		}
		else
		{
			break;
		}
	}
	//std::cout << lastCurrentCell->value << std::endl;
	fitness_ = calcFitness(minDistanceFromGoal, lastCurrentCell, goal, start, i / 2, containsVisitedCell);
	//fitness = fitness_;
	return fitness_;
}

double Individual::getMaxFitness()
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

double Individual::calcFitness(int minDist, std::shared_ptr<Cell> currentCell, std::shared_ptr<Cell> goal, std::shared_ptr<Cell> start, int nSteps, bool containsVisitedCell)
{
	
	//int distanceFromGoal = std::abs((int)currentCell->col - (int)goal->col) + std::abs((int)currentCell->row - (int)goal->row);
	
	//int distanceFromGoal = std::abs((int)currentCell->col);
	/*if (distanceFromGoal < minDistanceFromGoal)
	{
		//setMinDistanceFromGoal(individual, distanceFromGoal);
		minDistanceFromGoal = distanceFromGoal;
	}
	else
	{
		distanceFromGoal = minDistanceFromGoal;
	}*/
	
	//int distanceFromStart = std::abs((int)currentCell->col - (int)start->col) + std::abs((int)currentCell->row - (int)start->row);
	// TODO: make this more intelligent
	//return 10 - 0.01*distanceFromGoal +  nSteps;
	//return distanceFromStart + 2.1*nSteps - distanceFromGoal;
	//return nSteps;
	int containsVisitedCellFee = 0;
	if (containsVisitedCell) containsVisitedCellFee = 10000;

	return 10 - minDist +  0.1*nSteps - containsVisitedCellFee;
}
