#pragma once

#include "Cell.h"
#include <vector>
//#include "Display.h"
#include <random>

class Maze
{
public:
	Maze(int, int);
	Maze() = default;
	std::shared_ptr<Cell> root;
	//Display display;
	std::shared_ptr<Cell> carve(std::shared_ptr<Cell> currCell);
	int height;
	int width;

	
	std::vector< std::shared_ptr<Cell> > unvisitedNeighbors;
	std::vector< std::shared_ptr<Cell> > stack;
	int step = 0;

	std::vector<std::shared_ptr<Cell>> cells;

	int getCellRow(std::shared_ptr<Cell> cell);
	int getCellColumn(std::shared_ptr<Cell> cell);
	void removeWall(std::shared_ptr<Cell>& currCell, std::shared_ptr<Cell>& neighbor);
private:
	void getUnvisitedNeighbors(std::shared_ptr<Cell> &currCell, std::vector<std::shared_ptr<Cell>> &unvisitedNeighbors);
};

