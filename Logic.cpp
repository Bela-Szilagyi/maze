#include "Logic.h"



Logic::Logic()
{
}


Logic::Logic(int height, int width) : maze(height, width)
{
}

Logic::~Logic()
{
}

bool Logic::handleEvents(SDL_Event &event)
{
	return event.type == SDL_QUIT ? true : false;
	/*
	if (event.type == SDL_QUIT)
	{
		return true;
	}
	return false;
	*/
}

Maze Logic::getMaze()
{
	return maze;
}

bool Logic::popup()
{
	const SDL_MessageBoxButtonData buttons[] = {
		{ /* .flags, .buttonid, .text */        0, 0, "no" },
	{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
	};
	const SDL_MessageBoxColorScheme colorScheme = {
		{ /* .colors (.r, .g, .b) */
		  /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
			{ 255,   0,   0 },
			/* [SDL_MESSAGEBOX_COLOR_TEXT] */
	{ 0, 255,   0 },
	/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
	{ 255, 255,   0 },
	/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
	{ 0,   0, 255 },
	/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
	{ 255,   0, 255 }
		}
	};
	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION, /* .flags */
		NULL, /* .window */
		"Maze generated!", /* .title */
		"Generate another one?", /* .message */
		SDL_arraysize(buttons), /* .numbuttons */
		buttons, /* .buttons */
		&colorScheme /* .colorScheme */
	};
	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		SDL_Log("error displaying message box");
		return 1;
	}
	/*
	if (buttonid == -1) {
	SDL_Log("no selection");
	}
	else {
	SDL_Log("selection was %s", buttons[buttonid].text);
	}
	*/
	return buttonid;
}

void Logic::run()
{
	Display::printMaze(maze);
	display.init();
	bool quit = false;
	Uint32 timePassed = 0;
	Uint32 timeStep = 16;
	ARobot aRobot(maze);
	bool doSomething = false;
	while (!quit)
	{
		timePassed = SDL_GetTicks();
		SDL_Event SDL_event;
		while (SDL_PollEvent(&SDL_event) != 0)
		{
			quit = handleEvents(SDL_event);
			std::shared_ptr<Cell> currCell = maze.root; //1. Make the initial cell the current cell
														//currCell->isVisited = true;	//and mark it as visited
			do
			{
				currCell = maze.carve(currCell);
				display.showMaze(maze, currCell);
				if (SDL_PollEvent(&SDL_event) != 0 && SDL_event.type == SDL_QUIT) {
					//if (SDL_event.type == SDL_QUIT) {
						quit = handleEvents(SDL_event);
						break;
					//}
				}
				std::cout << "carving\n";
			} while (!(maze.unvisitedNeighbors.empty() && maze.stack.empty())); //2. While there are unvisited cells
			while (!doSomething)
			{
				aRobot.getInfo();
				doSomething = true;
			} 
			while (timePassed + timeStep > SDL_GetTicks())
			{
				SDL_Delay(0);
			}
		}
	}
}
