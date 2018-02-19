#include "Display.h"

/*
void Display::printMazeValues(Maze m)
{
	std::shared_ptr<Cell> firstInRow = m.root;
	while (true)
	{
		std::shared_ptr<Cell> actCell = firstInRow;
		while (true)
		{
			actCell->nWall ? std::cout << "---" : std::cout << "   ";
			if (actCell->eNeighbor) actCell = actCell->eNeighbor;
			else break;
		};
		std::cout << std::endl;
		actCell = firstInRow;
		while (true)
		{
			actCell->wWall ? std::cout << "|" : std::cout << " ";
			std::cout << actCell->value;
			actCell->eWall ? std::cout << "|" : std::cout << " ";
			if (actCell->eNeighbor) actCell = actCell->eNeighbor;
			else break;
		};
		std::cout << std::endl;
		actCell = firstInRow;
		while (true)
		{
			actCell->sWall ? std::cout << "---" : std::cout << "   ";
			if (actCell->eNeighbor) actCell = actCell->eNeighbor;
			else break;
		};
		std::cout << std::endl;
		if (firstInRow->sNeighbor) firstInRow = firstInRow->sNeighbor;
		else break;
	}
}
*/


void Display::printMaze(const Maze &m)
{
	std::shared_ptr<Cell> firstInRow = m.root;
	while (true)
	{
		std::shared_ptr<Cell> actCell = firstInRow;
		while (true)
		{
			actCell->nWall ? std::cout << "***" : std::cout << "   ";
			if (actCell->eNeighbor) actCell = actCell->eNeighbor;
			else break;
		};
		std::cout << std::endl;
		actCell = firstInRow;
		while (true)
		{
			actCell->wWall ? std::cout << "*" : std::cout << " ";
			std::cout << " ";
			actCell->eWall ? std::cout << "*" : std::cout << " ";
			if (actCell->eNeighbor) actCell = actCell->eNeighbor;
			else break;
		};
		std::cout << std::endl;
		actCell = firstInRow;
		while (true)
		{
			actCell->sWall ? std::cout << "***" : std::cout << "   ";
			if (actCell->eNeighbor) actCell = actCell->eNeighbor;
			else break;
		};
		std::cout << std::endl;
		if (firstInRow->sNeighbor) firstInRow = firstInRow->sNeighbor;
		else break;
	}
}


Display::Display()
	: window(nullptr), renderer(nullptr)
{
	//init();
	//background = loadTexture("MercatorEarth.png");

	/*
	SDL_RenderClear(renderer);
	//background->render(renderer, nullptr);
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	*/
}

void Display::showMaze(const Maze &m, const std::shared_ptr<Cell> currCell)
{
	int xOffset = 10;
	int yOffset = 10;
	int cellSize = 1300 / m.width < 700 / m.height ? 1300 / m.width : 700 / m.height;
	if (!currCell) //drawing entire maze
	{
		SDL_RenderClear(renderer);
		std::shared_ptr<Cell> actCell = m.root;
		std::shared_ptr<Cell> firstInRow = actCell;
		for (int row = 0; row < m.height; ++row)
		{
			actCell = firstInRow;
			for (int column = 0; column < m.width; ++column)
			{
				SDL_Rect rect;
				rect.x = xOffset + column * cellSize;
				rect.y = yOffset + row * cellSize;
				rect.w = cellSize;
				rect.h = cellSize;
				if (actCell == currCell) SDL_SetRenderDrawColor(renderer, 155, 193, 188, SDL_ALPHA_OPAQUE);
				else if (actCell->isInAStarPath) SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE); //yellow -> is in AStarPath
				else if (actCell->numOfAllWalls() == 3) SDL_SetRenderDrawColor(renderer, 230, 235, 224, SDL_ALPHA_OPAQUE); //platinum -> dead end
				else SDL_SetRenderDrawColor(renderer, 92, 164, 169, SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect(renderer, &rect);
				SDL_SetRenderDrawColor(renderer, 237, 106, 90, SDL_ALPHA_OPAQUE); //terra cotta
				int actCellLeftX = xOffset + column * cellSize;
				int actCellUpperY = yOffset + row * cellSize;
				if (actCell->nWall) SDL_RenderDrawLine(renderer, actCellLeftX, actCellUpperY, actCellLeftX + cellSize - 1, actCellUpperY);
				if (actCell->eWall) SDL_RenderDrawLine(renderer, actCellLeftX + cellSize - 1, actCellUpperY, actCellLeftX + cellSize - 1, actCellUpperY + cellSize - 1);
				if (actCell->sWall) SDL_RenderDrawLine(renderer, actCellLeftX + cellSize - 1, actCellUpperY + cellSize - 1, actCellLeftX, actCellUpperY + cellSize - 1);
				if (actCell->wWall) SDL_RenderDrawLine(renderer, actCellLeftX, actCellUpperY + cellSize - 1, actCellLeftX, actCellUpperY);
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); //black
				if (actCell->eNeighbor) actCell = actCell->eNeighbor;
			}
			if (firstInRow->sNeighbor) firstInRow = firstInRow->sNeighbor;
		}
	}
	else //if drawing curCell only
	{
		std::shared_ptr<Cell> actCell = m.root;
		std::shared_ptr<Cell> firstInRow = actCell;
		for (int row = 0; row < m.height; ++row)
		{
			actCell = firstInRow;
			for (int column = 0; column < m.width; ++column)
			{
				SDL_Rect rect;
				rect.x = xOffset + column * cellSize;
				rect.y = yOffset + row * cellSize;
				rect.w = cellSize;
				rect.h = cellSize;
				if (actCell == currCell)
				{
					SDL_SetRenderDrawColor(renderer, 155, 193, 188, SDL_ALPHA_OPAQUE);
					SDL_RenderFillRect(renderer, &rect);
					break;
				}
			}
			if (firstInRow->sNeighbor) firstInRow = firstInRow->sNeighbor;
		}
	}
	SDL_RenderPresent(renderer);
}

Display::~Display() {
	std::cout << "display object was destroyed";
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);
	//IMG_Quit();
	SDL_Quit();
}

bool Display::createWindow() {
	window = SDL_CreateWindow("Happy Vampires: Maze", 40, 40, 1300, 700, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

bool Display::createRenderer() {
	if (!window) return false;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

/*
bool Graphics::initSDLImage() {
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}
	return true;
}
*/

bool Display::init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}
	if (!createWindow()) return false;
	if (!createRenderer()) return false;
	//if (!initSDLImage()) return false;
	return true;
}