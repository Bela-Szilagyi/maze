#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "Maze.h"
#include "Display.h"
#include "Robot.h"
#include "ARobot.h"


enum LogicalState 
{
	create,
	makeMazeUnperfect,
	aStar,
	closeWindow
};

class Logic
{
public:
	Logic();
	Logic(int height, int width);
	~Logic();
	void run();
	void doLogic();
	void createMaze();
	void makeUnperfect();
private:
	bool handleEvents(SDL_Event &event);
	bool popup();
	Maze getMaze();

	Display display;
	Maze maze;
	LogicalState logicalState;
};

