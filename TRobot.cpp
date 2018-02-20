#include "TRobot.h"



TRobot::TRobot(Maze & maze) : maze(maze)
{
	actCell = (maze.root);
	std::cout << "tRobot created, root's eWall is " << maze.root->eWall << " sWall is " << maze.root->sWall << '\n';
}

TRobot::TRobot()
{
}

TRobot::~TRobot()
{
}

std::vector< std::shared_ptr<Cell> > TRobot::solveMaze()
{
	std::vector< std::shared_ptr<Cell> > path{};
	std::shared_ptr<Cell> start = actCell;
	std::shared_ptr<Cell> current = start;
	std::shared_ptr<Cell> cameFrom = nullptr;
	int indexOfLastElement = maze.width * maze.height - 1;
	std::shared_ptr<Cell> goal = maze.cells[indexOfLastElement];
	bool markNeeded = false;

	while (current != goal)
	{
		path.push_back(current);
		std::cout << "Current value: " << current->value << " unMarked neighbors: ";
		int numberOfNeighbors = 4 - current->numOfAllWalls();
		std::vector<std::shared_ptr<Cell>> unmarkedNeighbors;
		std::vector<std::shared_ptr<Cell>> markedNeighbors;
		getNeighborInfo(current, markedNeighbors, unmarkedNeighbors);
		for (int i = 0; i < unmarkedNeighbors.size(); ++i) if(unmarkedNeighbors[i]) std::cout << unmarkedNeighbors[i]->value << ", ";
		std::cout << "marked neighbors: " << std::endl;
		for (int i = 0; i < markedNeighbors.size(); ++i) if(markedNeighbors[i]) std::cout << markedNeighbors[i]->value << ", ";
		
		if (numberOfNeighbors <= 2)
		{
			markNeeded = false;
			Step(cameFrom, current, unmarkedNeighbors, markedNeighbors, markNeeded);
			//current->isMarkedByTremaux = true;
			//std::cout << "next value: " << current->value << std::endl;
		}
		else
		{
			markNeeded = true;
			if(unmarkedNeighbors.size() > 0)
			{
				Step(cameFrom, current, unmarkedNeighbors, markedNeighbors, markNeeded);
				std::cout << "next value: " << current->value << std::endl;
				//current->isMarkedByTremaux = true;
				current->isMarkedByTremaux = true;
			}
			else
			{
				//break;
				//current->isMarkedByTremaux = true;
				std::cout << "next value: " << current->value << std::endl;
				current = cameFrom;
				current->isMarkedByTremaux = true;
			}
		}
		std::cout << std::endl;
		//break;
		//current = ....
	}


	//std::vector< std::shared_ptr<Cell> > result;
	//result.push_back(nullptr);
	return path;
}

void TRobot::Step(std::shared_ptr<Cell> &cameFrom, std::shared_ptr<Cell> &current, std::vector<std::shared_ptr<Cell>> &unmarkedNeighbors, std::vector<std::shared_ptr<Cell>> &markedNeighbors, bool markNeeded)
{
	std::shared_ptr<Cell> next;
	findNextCell(unmarkedNeighbors, cameFrom, next, markedNeighbors);
	cameFrom = current;
	current = next;
}

void TRobot::findNextCell(std::vector<std::shared_ptr<Cell>> &unmarkedNeighbors, std::shared_ptr<Cell> &cameFrom, std::shared_ptr<Cell> &next, std::vector<std::shared_ptr<Cell>> &markedNeighbors)
{
	for (int i = 0; i < unmarkedNeighbors.size(); ++i)
	{
		if (unmarkedNeighbors[i] != cameFrom && unmarkedNeighbors[i] != nullptr)
		{
			next = unmarkedNeighbors[i]; //std::cout << next->value << ". ";
			break;
		}
	}
	if (!next)
	{
		for (int i = 0; i < markedNeighbors.size(); ++i)
		{
			if (markedNeighbors[i] != cameFrom && markedNeighbors[i] != nullptr)
			{
				next = markedNeighbors[i];
				break;
			}
		}
	}
}

void TRobot::getNeighborInfo(std::shared_ptr<Cell> &current, std::vector<std::shared_ptr<Cell>> &markedNeighbors, std::vector<std::shared_ptr<Cell>> &unmarkedNeighbors)
{
	if (!current->nWall)
	{
		if (current->nNeighbor->isMarkedByTremaux) markedNeighbors.push_back(current->nNeighbor);
		else unmarkedNeighbors.push_back(current->nNeighbor);
	}
	if (!current->eWall)
	{
		if (current->eNeighbor->isMarkedByTremaux) markedNeighbors.push_back(current->eNeighbor);
		else unmarkedNeighbors.push_back(current->eNeighbor);
	}
	if (!current->sWall)
	{
		if (current->sNeighbor->isMarkedByTremaux) markedNeighbors.push_back(current->sNeighbor);
		else unmarkedNeighbors.push_back(current->sNeighbor);
	}
	if (!current->wWall)
	{
		if (current->wNeighbor->isMarkedByTremaux) markedNeighbors.push_back(current->wNeighbor);
		else unmarkedNeighbors.push_back(current->wNeighbor);
	}
}
