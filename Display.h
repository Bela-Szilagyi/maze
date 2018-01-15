#pragma once
#include "Maze.h"

class Display
{
public:
	Display();
	~Display();
	void printMazeValues(Maze m);
	static void printMaze(const Maze&);
};


