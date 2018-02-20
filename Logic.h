#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "Maze.h"
#include "Display.h"
#include "Robot.h"
#include "ARobot.h"
#include "TRobot.h"


enum LogicalState 
{
	create,
	makeMazeUnperfect,
	aStar,
	tremaux,
	systemPause,
	closeWindow
};

class Logic
{
public:
	Logic();
	Logic(int height, int width);
	~Logic();
	void run();
	bool doLogic();
	void createMaze();
	void makeUnperfect();
	void AStarSolveMaze();
	void tremauxSolveMaze();
	void pauseSystem();
private:
	bool handleEvents(SDL_Event &event);
	bool popup();
	Maze getMaze();

	Display display;
	Maze maze;
	LogicalState logicalState;
};

