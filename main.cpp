#include "Generator.h"

bool handleEvents(SDL_Event &event)
{
	if (event.type == SDL_QUIT)
	{
		std::cout << "quit\n";
		return true;
	}
	return false;
}

bool popup()
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
	if (buttonid == -1) {
		SDL_Log("no selection");
	}
	else {
		SDL_Log("selection was %s", buttons[buttonid].text);
	}
	return buttonid;
}


int main(int argc, char *args[])
{
	bool another;
	Maze maze;
	bool quit = false;
	while (!quit)
	{
		SDL_Event sdl_event;
		do
		{
			Generator generator(15, 30); //Generator generator(30, 60);
			Display display;
			maze = generator.generate();

			//display.showMaze(maze);

			//maze.carve();
			std::shared_ptr<Cell> currCell = maze.root; //1. Make the initial cell the current cell 
														//currCell->isVisited = true;	//and mark it as visited

			do
			{
				currCell = maze.carve(currCell);
				display.showMaze(maze, currCell);
				while (SDL_PollEvent(&sdl_event) != 0)
				{
					quit = handleEvents(sdl_event);
				}
			} while (!maze.unvisitedNeighbors.empty() || !maze.stack.empty()); //2. While there are unvisited cells
			another = popup();
			std::cout << another << '\n';
		} while (another);
	}
	
	
	//display.showMaze(maze);
	system("pause");
	return 0;
}

