#pragma once
#include "Robot.h"
#include <set>
#include <map>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "Display.h"

class ARobot :	public Robot
{
public:
	ARobot(Maze & maze, Display & display);
	ARobot();
	~ARobot();
	virtual std::vector< std::shared_ptr<Cell> > solveMaze() override;
	void getInfo();
private:
	Maze maze;
	unsigned int heuristicCostEstimate(unsigned int gValue, std::shared_ptr<Cell> start, std::shared_ptr<Cell> goal);
	std::vector< std::shared_ptr<Cell> > reconstructPath(std::map< std::shared_ptr<Cell>, std::shared_ptr<Cell> > cameFrom, std::shared_ptr<Cell> current);
	Display display;
};

