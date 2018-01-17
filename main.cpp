#include "Generator.h"


int main(int argc, char *args[])
{
	Generator generator(60, 120);
	Maze maze = generator.generate();
	Display display;
	display.showMaze(maze);
	maze.carve();
	display.showMaze(maze);
	system("pause");
	return 0;
}