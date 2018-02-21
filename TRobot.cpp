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

	while (current != goal)
	{
		path.push_back(current);
		int numberOfNeighbors = 4 - current->numOfAllWalls();
		std::vector<std::shared_ptr<Cell>> unmarkedNeighbors;
		std::vector<std::shared_ptr<Cell>> markedNeighbors;
		getNeighborInfo(current, markedNeighbors, unmarkedNeighbors);
		if (numberOfNeighbors <= 2)
		{
			Step(cameFrom, current, unmarkedNeighbors, markedNeighbors);
			current->isMarkedByTremaux = true;
		}
		else
		{
			if(unmarkedNeighbors.size() > 0)
			{
				Step(cameFrom, current, unmarkedNeighbors, markedNeighbors);
				current->isMarkedByTremaux = true;
			}
			else
			{
				current->availableNeighbors = markedNeighbors;
				int index = current->availableNeighborCnt % markedNeighbors.size();
				++current->availableNeighborCnt;
				cameFrom = current;
				current = markedNeighbors[index];
				current->isMarkedByTremaux = true;
			}
		}
	}
	path.push_back(current);
	return path;
}

void TRobot::Step(std::shared_ptr<Cell> &cameFrom, std::shared_ptr<Cell> &current, std::vector<std::shared_ptr<Cell>> &unmarkedNeighbors, std::vector<std::shared_ptr<Cell>> &markedNeighbors)
{
	std::shared_ptr<Cell> next;
	findNextCell(unmarkedNeighbors, cameFrom, next, markedNeighbors);
	if (!next)
	{
		next = cameFrom;
	}
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
