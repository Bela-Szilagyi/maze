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


bool Logic::doLogic()
{
	//display.showMaze(maze, maze.root);
	//SDL_Delay(2000);
	if (logicalState == create)
	{
		createMaze();
		return false;
	}
	else if (logicalState == makeMazeUnperfect)
	{
		makeUnperfect();
		return false;
	}
	else if (logicalState == aStar)
	{
		AStarSolveMaze(); //std::cout << "AStar algo begins\n";
		return false;
	}
	else if (logicalState == tremaux)
	{
		tremauxSolveMaze();
		return false;
	}
	else if (logicalState == systemPause) { 
		pauseSystem();
		return false;
	}
	else if (logicalState == closeWindow) return true;
}

void Logic::createMaze()
{
	std::shared_ptr<Cell> currCell = maze.root; //1. Make the initial cell the current cell
												//currCell->isVisited = true;	//and mark it as visited
	
	SDL_Event SDL_event;
	do
	{

		currCell = maze.carve(currCell);
		//display.showMaze(maze, currCell);
		if (SDL_PollEvent(&SDL_event) != 0 && SDL_event.type == SDL_QUIT) {
			logicalState = closeWindow;
			return;
		}
		//std::cout << "carving\n";
	} while (!(maze.unvisitedNeighbors.empty() && maze.stack.empty())); //2. While there are unvisited cells
	
	
	/*maze.removeWall(currCell, currCell->sNeighbor);
	currCell = currCell->eNeighbor;
	maze.removeWall(currCell, currCell->sNeighbor);
	maze.removeWall(currCell, currCell->eNeighbor);
	currCell = currCell->eNeighbor;
	maze.removeWall(currCell, currCell->eNeighbor);
	currCell = currCell->eNeighbor;
	maze.removeWall(currCell, currCell->eNeighbor);
	currCell = currCell->eNeighbor;
	maze.removeWall(currCell, currCell->sNeighbor);
	currCell = currCell->sNeighbor;
	maze.removeWall(currCell, currCell->sNeighbor);
	maze.removeWall(currCell, currCell->wNeighbor);
	currCell = currCell->wNeighbor;
	maze.removeWall(currCell, currCell->wNeighbor);
	currCell = currCell->wNeighbor;
	maze.removeWall(currCell, currCell->sNeighbor);
	currCell = currCell->wNeighbor;
	maze.removeWall(currCell, currCell->sNeighbor);
	currCell = currCell->wNeighbor;
	maze.removeWall(currCell, currCell->sNeighbor);
	currCell = currCell->sNeighbor;
	maze.removeWall(currCell, currCell->eNeighbor);
	currCell = currCell->eNeighbor;
	maze.removeWall(currCell, currCell->eNeighbor);
	*/
	//logicalState = makeMazeUnperfect;
	logicalState = tremaux;

	//logicalState = aStar;
}

void Logic::makeUnperfect()
{
	display.showMaze(maze, nullptr);
	std::cout << "Making maze unperfect\n";
	// for randomization
	std::random_device device;
	std::mt19937 generator(device());
	//std::uniform_int_distribution<int> distribution(0, ... - 1);
	//int randomNumber = distribution(generator);
	SDL_Event SDL_event;
	for (auto & cell : maze.cells)
	{
		//if cell has 3 walls, "randomly" remove wall: 
		if (cell->numOfAllWalls() == 3)
		{
			//	decide if remove randomly
			std::uniform_int_distribution<int> distribution(1, 10);
			int randomNumber = distribution(generator);
			//if (randomNumber > 7)
			{
				std::vector< std::shared_ptr<Cell> > neighbors;
				if (cell->nWall && cell->nNeighbor) neighbors.push_back(cell->nNeighbor);
				if (cell->eWall && cell->eNeighbor) neighbors.push_back(cell->eNeighbor);
				if (cell->sWall && cell->sNeighbor) neighbors.push_back(cell->sNeighbor);
				if (cell->wWall && cell->wNeighbor) neighbors.push_back(cell->wNeighbor);
				std::uniform_int_distribution<int> distribution(0, neighbors.size() - 1);
				int randomWall = distribution(generator);
				std::shared_ptr<Cell> neighbor = neighbors[randomWall];
				maze.removeWall(cell, neighbor);
			}
		}
		
		//display.showMaze(maze, cell);
		if (SDL_PollEvent(&SDL_event) != 0 && SDL_event.type == SDL_QUIT) {
			logicalState = closeWindow;
			return;
		}
	}
	std::cout << "Making maze unperfect done\n";
	display.showMaze(maze, nullptr);
	//logicalState = aStar;
	logicalState = tremaux;
}

void Logic::AStarSolveMaze()
{
	ARobot aRobot(maze);
	std::vector< std::shared_ptr<Cell> > path = aRobot.solveMaze();

	//std::cout << "Path size: " << path.size() << '\n';
	SDL_Event SDL_event;

	for (auto& cella : path) {
		cella->isInAStarPath = true;
		display.showMaze(maze, cella);
		if (SDL_PollEvent(&SDL_event) != 0 && SDL_event.type == SDL_QUIT) {
			logicalState = closeWindow;
			return;
		}
		//SDL_Delay(200);
	}
	logicalState = tremaux;

}

void Logic::tremauxSolveMaze()
{
	SDL_Event SDL_event;
	//std::cout << "Tremaux started" << std::endl;
	TRobot trobot(maze);
	std::vector< std::shared_ptr<Cell> > path = trobot.solveMaze();
	for (auto& cella : path) {
		cella->isInAStarPath = true;
		display.showMaze(maze, cella);
		if (SDL_PollEvent(&SDL_event) != 0 && SDL_event.type == SDL_QUIT) {
			logicalState = closeWindow;
			return;
		}
	}
	logicalState = systemPause;
}

void Logic::pauseSystem()
{
	SDL_Event SDL_event;
	//display.showMaze(maze, maze.root);
	display.showMaze(maze, nullptr);
	if (SDL_PollEvent(&SDL_event) != 0 && SDL_event.type == SDL_QUIT) {
		logicalState = closeWindow;
		return;
	}
}


void Logic::run()
{
	//Display::printMaze(maze);
	display.init();
	logicalState = create;
	bool quit = false;
	Uint32 timePassed = 0;
	Uint32 timeStep = 16;
	while (!quit)
	{
		timePassed = SDL_GetTicks();
		// SDL_Event SDL_event;
		// while (SDL_PollEvent(&SDL_event) != 0)
		//{
			// quit = handleEvents(SDL_event);
			quit = doLogic();
			//quit = true;
			while (timePassed + timeStep > SDL_GetTicks()) SDL_Delay(0);
		//}
	}
	//system("pause");
}