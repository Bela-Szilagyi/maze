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
	void showMaze(const Maze &m, const std::shared_ptr<Cell> currCell, const std::shared_ptr<Cell> currCell2 = nullptr);
private:
	SDL_Window * window;
	SDL_Renderer *renderer;

	bool createWindow();
	bool createRenderer();
	//bool initSDLImage();
};


