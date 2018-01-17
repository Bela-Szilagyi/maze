#pragma once
#include <SDL.h>
#include <memory>
#include <iostream>
#include "Maze.h"

//#include <SDL_image.h>

class Display
{
public:
	Display();
	~Display();

	SDL_Renderer* getRenderer() { return renderer; }
	bool init();
	//void printMazeValues(Maze m);
	static void printMaze(const Maze &m);
	void showMaze(const Maze &m);
private:
	SDL_Window * window;
	SDL_Renderer *renderer;

	bool createWindow();
	bool createRenderer();
	//bool initSDLImage();
};


