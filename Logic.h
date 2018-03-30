#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "Maze.h"
#include "Display.h"
#include "Robot.h"
#include "ARobot.h"
#include "TRobot.h"
#include "Button.h"
#include "GeneticAlgorithm.h"


enum LogicalState 
{
	waitToStart,
	create,
	makeMazeUnperfect,
	aStar,
	tremaux,
	GA,
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
	void waitToStartButtonPush();
	void createMaze();
	void makeUnperfect();
	void AStarSolveMaze();
	void GASolveMaze();
	void tremauxSolveMaze();
	void pauseSystem();
private:
	void handleEvents(SDL_Event &event);
	bool popup();
	Maze getMaze();

	Display display;
	Maze maze;
	LogicalState logicalState;
	int clickedX = -1; int clickedY = -1;
};

