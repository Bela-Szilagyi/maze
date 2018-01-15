#include <iostream>
#include <vector>
#include <memory>
#include "Maze.h"
#include "Display.h"


int main()
{
	Maze maze(4, 3); //Maze maze(10, 36);
					 //Display::printMazeValues(maze);
	Display::printMaze(maze);
	maze.carve();
	system("pause");
	return 0;
}