#include "ARobot.h"

struct cellCompare {
	bool operator()(const std::shared_ptr<Cell> first, const std::shared_ptr<Cell> second) const
	{
		if (first->fScore < second->fScore) return true;
		else if (first->fScore > second->fScore) return false;
		else if (first->gScore < second->gScore) return true;
		else if (first->gScore > second->gScore) return false;
		else return first->value < second->value;
	}
} setObject;


ARobot::ARobot(Maze & maze, Display & display) : maze(maze), display(display)
{
	actCell = (maze.root);
	std::cout << "aRobot created, root's eWall is " << maze.root->eWall << " sWall is " << maze.root->sWall << '\n';
}

ARobot::ARobot()
{
}

ARobot::~ARobot()
{
}

std::vector< std::shared_ptr<Cell> > ARobot::solveMaze()
{
	std::vector< std::shared_ptr<Cell> > path{};
	std::shared_ptr<Cell> start = actCell;
	int indexOfLastElement = maze.width * maze.height - 1;
	std::shared_ptr<Cell> goal = maze.cells[indexOfLastElement];
	std::set< std::shared_ptr<Cell> > closedSet;
	std::set< std::shared_ptr<Cell>, cellCompare > openSet;
	openSet.insert(start);
	std::map< std::shared_ptr<Cell>, std::shared_ptr<Cell> > cameFrom;
	
	std::map < std::shared_ptr<Cell>, unsigned int > gScore;
	for (auto& cell : maze.cells)
	{
		gScore[cell] = 0 - 1;
		cell->gScore = gScore[cell];
	}
	gScore[start] = 0;
	
	std::map < std::shared_ptr<Cell>, unsigned int > fScore;
	for (auto& cell : maze.cells)
	{
		fScore[cell] = 0 - 1;
		cell->fScore = fScore[cell];
	};
	fScore[start] = heuristicCostEstimate(gScore[start], start, goal);
	
	std::shared_ptr<Cell> current = nullptr;

	while (!openSet.empty()) {
		current = *openSet.begin();
		if (current == goal) {
			return reconstructPath(cameFrom, current);
		}
		openSet.erase(current);
		closedSet.insert(current);

		for (int i = 0; i < 4; ++i) {
			std::shared_ptr<Cell> neighbor = nullptr;
			if (i == 0 && !current->nWall) neighbor = current->nNeighbor;
			if (i == 1 && !current->eWall) neighbor = current->eNeighbor;
			if (i == 2 && !current->sWall) neighbor = current->sNeighbor;
			if (i == 3 && !current->wWall) neighbor = current->wNeighbor;
			if (neighbor) {
				if (closedSet.find(neighbor) != closedSet.end()) continue;
				if (openSet.find(neighbor) == openSet.end()) 
				{
					openSet.insert(neighbor);
				}
				auto tentativeGScore = gScore[current] + 1;
				if (tentativeGScore >= gScore[neighbor]) continue;
				cameFrom[neighbor] = current;
				gScore[neighbor] = tentativeGScore;
				fScore[neighbor] = heuristicCostEstimate(gScore[neighbor], neighbor, goal);
			}
		}
	}		
	return path;
}

void ARobot::getInfo()
{
	std::cout << "maze carved, root's eWall is " << actCell->eWall << " sWall is " << actCell->sWall << '\n';
}

unsigned int ARobot::heuristicCostEstimate(unsigned int gValue, std::shared_ptr<Cell> start, std::shared_ptr<Cell> goal)
{
	// using Manhattan distance for hValue
	unsigned int hValue = std::abs((int) start->col - (int) goal->col) + std::abs((int) start->row - (int) goal->row);
	unsigned int fValue = gValue + hValue;
	return fValue;
}

std::vector< std::shared_ptr<Cell> > ARobot::reconstructPath(std::map< std::shared_ptr<Cell>, std::shared_ptr<Cell> > cameFrom, std::shared_ptr<Cell> current)
{
	std::vector< std::shared_ptr<Cell> > totalPath;
	totalPath.push_back(current);
	while (cameFrom[current])
	{
		current = cameFrom[current];
		totalPath.push_back(current);
	}
	std::reverse(std::begin(totalPath), std::end(totalPath));
	return totalPath;
}