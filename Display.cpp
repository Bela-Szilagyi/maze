#include "Display.h"


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
	init();
	//background = loadTexture("MercatorEarth.png");

	SDL_RenderClear(renderer);
	//background->render(renderer, nullptr);
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
}

Display::~Display() {
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);
	//IMG_Quit();
	SDL_Quit();
}

bool Display::createWindow() {
	window = SDL_CreateWindow("Happy Vampires: Maze", 40, 40, 823, 698, SDL_WINDOW_SHOWN);
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