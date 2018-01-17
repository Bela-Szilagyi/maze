#include "Generator.h"
#include "Displayer.h"


int main(int argc, char *args[])
{
	Generator generator(10, 10);
	Maze maze = generator.generate();
	Display display;
	Displayer displayer(maze, display);
	displayer.show(maze);
	//maze.carve();
	//displayer.show(maze);
	system("pause");
	return 0;
}