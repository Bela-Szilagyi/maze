#include "Displayer.h"



Displayer::Displayer()
{
}


Displayer::~Displayer()
{
}

void Displayer::show(const Maze &m)
{
	display.showMaze(maze);
}
