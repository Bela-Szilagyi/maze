#pragma once
#include "Robot.h"

class ARobot :	public Robot
{
public:
	ARobot(Maze & maze);
	ARobot();
	~ARobot();
	virtual std::vector< std::shared_ptr<Cell> > solveMaze() override;
	void getInfo();
};

