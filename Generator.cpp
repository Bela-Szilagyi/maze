#include <iostream>
#include "Generator.h"


Generator::Generator()
{
}

Generator::Generator(int height, int width) : maze(height, width)
{
	
}


Generator::~Generator()
{
}

void Generator::generate()
{
	//Maze maze(4, 3); //Maze maze(10, 36);
					 //Display::printMazeValues(maze);
	//
	//maze = std::make_unique<Maze>(height, width);
	//maze
	Display::printMaze(maze);
	maze.carve();
}
