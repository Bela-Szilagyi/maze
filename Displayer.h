#pragma once
#include "Display.h"
#include "Maze.h"

class Displayer
{
public:
	Displayer();
	~Displayer();
	Displayer(Maze maze, Display display) : maze(maze), display(display) {};
	void show(const Maze &m);
	Maze maze;
	Display display;
};

