#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Maze.h"
#include "Display.h"

class Generator
{
public:
	Generator();
	Generator (int height, int width);
	~Generator();

	void generate();
private:
	Display display;
	Maze maze;
};

