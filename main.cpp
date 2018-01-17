#include "Generator.h"


int main(int argc, char *args[])
{
	Generator generator(15, 30);
	Maze maze = generator.generate();
	Display display;
	display.showMaze(maze);
	
	//maze.carve();
	std::shared_ptr<Cell> currCell = maze.root; //1. Make the initial cell the current cell 
	//currCell->isVisited = true;	//and mark it as visited

	do
	{
		currCell = maze.carve(currCell);
		display.showMaze(maze);
	} while (!maze.unvisitedNeighbors.empty() || !maze.stack.empty()); //2. While there are unvisited cells

	display.showMaze(maze);
	system("pause");
	return 0;
}