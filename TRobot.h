#pragma once
#include "Robot.h"
#include <set>
#include <map>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "Display.h"
#include <iostream>

class TRobot : public Robot
{
public:
	TRobot(Maze & maze);
	TRobot();
	~TRobot();
	virtual std::vector< std::shared_ptr<Cell> > solveMaze() override;
	void Step(std::shared_ptr<Cell> &cameFrom, std::shared_ptr<Cell> &current, std::vector<std::shared_ptr<Cell>> &unmarkedNeighbors, std::vector<std::shared_ptr<Cell>> &markedNeighbors, bool markNeeded);
	void findNextCell(std::vector<std::shared_ptr<Cell>> &unmarkedNeighbors, std::shared_ptr<Cell> &cameFrom, std::shared_ptr<Cell> &next, std::vector<std::shared_ptr<Cell>> &markedNeighbors);
	void getNeighborInfo(std::shared_ptr<Cell> &current, std::vector<std::shared_ptr<Cell>> &markedNeighbors, std::vector<std::shared_ptr<Cell>> &unmarkedNeighbors);
private:
	Maze maze;
};


