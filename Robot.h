#pragma once
#include <memory>
#include <iostream>
#include <vector>
#include "Maze.h"

class Robot
{
public:
	Robot();
	~Robot();
	virtual std::vector< std::shared_ptr<Cell> > solveMaze() = 0;
protected:
	std::shared_ptr<Cell> actCell;
};

