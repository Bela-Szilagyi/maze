#include "ARobot.h"

struct cellCompare {
	bool operator()(const std::shared_ptr<Cell> first, const std::shared_ptr<Cell> second) const
	{
		return first->fScore < second->fScore;
	}
} setObject;


ARobot::ARobot(Maze & maze) : maze(maze)
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
	//path.push_back(nullptr);
	std::shared_ptr<Cell> start = actCell;
	int indexOfLastElement = maze.width * maze.height - 1;
	std::shared_ptr<Cell> goal = maze.cells[indexOfLastElement];
	//std::multiset< std::shared_ptr<Cell> > closedSet;
	std::vector< std::shared_ptr<Cell> > closedSet;
	//std::multiset< std::shared_ptr<Cell>, cellCompare > openSet;
	std::vector< std::shared_ptr<Cell> > openSet;
	openSet.push_back(start);
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

		//std::cout << "openSet (" << openSet.size() << "): "; for (auto & item : openSet) std::cout << item->value << ' ';
		//std::cout << "\nclosedSet (" << closedSet.size() << "): "; for (auto & item : closedSet) std::cout << item->value << ' '; std::cout << '\n';
		std::sort(openSet.begin(), openSet.end(), setObject);
		current = *openSet.begin();
		//std::cout << "current: " << current->value << '\n';
		if (current == goal) {
			return reconstructPath(cameFrom, current);
		}
		//std::cout << "erasing: " << current->value << " from openSet\n";
		openSet.erase(openSet.begin()); // current
		//std::cout << "\topenSet (" << openSet.size() << "): "; for (auto & item : openSet) std::cout << item->value << ' ';
		//std::cout << '\n';
		//std::cout << "inserting: " << current->value << " to closedSet\n";
		closedSet.push_back(current);
		//std::cout << "\tclosedSet (" << closedSet.size() << "): "; for (auto & item : closedSet) std::cout << item->value << ' ';
		//std::cout << '\n';

		for (int i = 0; i < 4; ++i) {
			std::shared_ptr<Cell> neighbor = nullptr;
			if (i == 0 && !current->nWall) neighbor = current->nNeighbor;
			if (i == 1 && !current->eWall) neighbor = current->eNeighbor;
			if (i == 2 && !current->sWall) neighbor = current->sNeighbor;
			if (i == 3 && !current->wWall) neighbor = current->wNeighbor;
			if (neighbor) {
				//std::cout << "i: " << i << " neighbor: " << neighbor->value << '\n';
				if (std::find(closedSet.begin(), closedSet.end(), neighbor) != closedSet.end())
				{
					//std::cout << "\tneighbor in closedSet: " << neighbor->value << '\n';
					continue;
				}
				//if (openSet.find(neighbor) == openSet.end()) 
				if (std::find(openSet.begin(), openSet.end(), neighbor) == openSet.end())
				{
					//std::cout << "\tinserting neighbor to openSet: " << neighbor->value << '\n';
					openSet.push_back(neighbor);
					//std::cout << "\topenSet (" << openSet.size() << "): "; for (auto & item : openSet) std::cout << item->value << ' ';
					//std::cout << '\n';
				}
				auto tentativeGScore = gScore[current] + 1;
				if (tentativeGScore >= gScore[neighbor]) continue;
				cameFrom[neighbor] = current;
				gScore[neighbor] = tentativeGScore;
				// check if gScore.... should be removed
				// fScore[neighbor] = gScore[neighbor] + heuristicCostEstimate(gScore[neighbor], neighbor, goal);
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
	// tryin Manhattan distance for hValue
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
	return totalPath;
}