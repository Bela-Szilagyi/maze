#include "ARobot.h"



ARobot::ARobot(Maze & maze)
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
	std::vector< std::shared_ptr<Cell> > path;
	path.push_back(nullptr);
	return path;
}

void ARobot::getInfo()
{
	std::cout << "maze carved, root's eWall is " << actCell->eWall << " sWall is " << actCell->sWall << '\n';
}