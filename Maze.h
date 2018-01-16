#pragma once

#include "Cell.h"
#include <vector>
//#include "Display.h"

class Maze
{
public:
	Maze(int, int);
	Maze() = default;
	std::shared_ptr<Cell> root;
	void carve();
private:
	//Display display;

	void removeWall(std::shared_ptr<Cell>& currCell, std::shared_ptr<Cell>& neighbor);
	void getUnvisitedNeighbors(std::shared_ptr<Cell> &currCell, std::vector<std::shared_ptr<Cell>> &unvisitedNeighbors);
};

