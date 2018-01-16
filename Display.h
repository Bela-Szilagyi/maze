#pragma once
#include <SDL.h>
#include <memory>
#include <iostream>
#include "Maze.h"

// this is a weird solution, but it works:
//#undef main


//#include <SDL_image.h>

class Display
{
public:
	Display();
	~Display();

	SDL_Renderer* getRenderer() { return renderer; }
	bool init();
	void printMazeValues(Maze m);
	static void printMaze(const Maze &m);
private:
	SDL_Window * window;
	SDL_Renderer *renderer;

	bool createWindow();
	bool createRenderer();
	//bool initSDLImage();
};


