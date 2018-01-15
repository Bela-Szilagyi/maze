#pragma once

#include "Cell.h"
#include <vector>

class Maze
{
public:
	Maze(int, int);
	std::shared_ptr<Cell> root;
	void carve();
private:
	void removeWall(std::shared_ptr<Cell>& currCell, std::shared_ptr<Cell>& neighbor);
	void getUnvisitedNeighbors(std::shared_ptr<Cell> &currCell, std::vector<std::shared_ptr<Cell>> &unvisitedNeighbors);
};

