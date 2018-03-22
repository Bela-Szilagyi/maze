#pragma once
#include <SDL.h>
#include <memory>
#include <iostream>
#include "Maze.h"
#include "Button.h"

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
	void showMaze(const Maze &m, const std::shared_ptr<Cell> currCell);
	void renderButtons();
	void addButton(std::shared_ptr<Button> button);
	std::shared_ptr<Button> getClickedButton(const int &x, const int &y) const;
private:
	SDL_Window * window;
	SDL_Renderer *renderer;
	std::vector<std::shared_ptr<Button>> buttonVector;

	bool createWindow();
	bool createRenderer();
	//bool initSDLImage();
};


