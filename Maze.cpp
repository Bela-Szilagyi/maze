#include "Maze.h"
#include "Display.h"
#include <iostream>

Maze::Maze(int rows, int columns) : height(rows), width(columns)
{
	std::vector<std::shared_ptr<Cell>> cells;
	for (int i = 0; i < rows * columns; ++i)
	{
		cells.emplace_back(std::make_shared<Cell>(i));
	}
	for (int i = 0; i < rows * columns; ++i)
	{
		//nNeighbor
		if (i >= columns) cells[i]->nNeighbor = cells[i - columns];
		//eNeighbor
		if ((i + 1) % columns != 0) cells[i]->eNeighbor = cells[i + 1];
		//sNeighbor
		if (i < (rows - 1) * columns) cells[i]->sNeighbor = cells[i + columns];
		//wNeighbor
		if (i % columns != 0) cells[i]->wNeighbor = cells[i - 1];
	}
	root = cells[0];


};

void Maze::removeWall(std::shared_ptr<Cell>& currCell, std::shared_ptr<Cell>& neighbor)
{
	if (currCell->nNeighbor == neighbor)
	{
		currCell->nWall = false;
		neighbor->sWall = false;
	}
	else if (currCell->eNeighbor == neighbor)
	{
		currCell->eWall = false;
		neighbor->wWall = false;
	}
	else if (currCell->sNeighbor == neighbor)
	{
		currCell->sWall = false;
		neighbor->nWall = false;
	}
	else //wNeighbor
	{
		currCell->wWall = false;
		neighbor->eWall = false;
	}
};

void Maze::getUnvisitedNeighbors(std::shared_ptr<Cell> &currCell, std::vector<std::shared_ptr<Cell>> &unvisitedNeighbors)
{
	if (currCell->nNeighbor && !currCell->nNeighbor->isVisited) unvisitedNeighbors.push_back(currCell->nNeighbor);
	if (currCell->eNeighbor && !currCell->eNeighbor->isVisited) unvisitedNeighbors.push_back(currCell->eNeighbor);
	if (currCell->sNeighbor && !currCell->sNeighbor->isVisited) unvisitedNeighbors.push_back(currCell->sNeighbor);
	if (currCell->wNeighbor && !currCell->wNeighbor->isVisited) unvisitedNeighbors.push_back(currCell->wNeighbor);
}

std::shared_ptr<Cell> Maze::carve(std::shared_ptr<Cell> currCell) //Recursive backtracker
{
	// for randomization
	std::random_device device;
	std::mt19937 generator(device());
	
	//std::shared_ptr<Cell> currCell = root; //1. Make the initial cell the /current cell 
	currCell->isVisited = true;	//and mark it as visited

	unvisitedNeighbors.clear();
	getUnvisitedNeighbors(currCell, unvisitedNeighbors);
	if (!unvisitedNeighbors.empty()) // 1. If the current cell has any neighbours which have not been visited
	{
		int numberOfUnvisitedNeighbors = unvisitedNeighbors.size();
		std::uniform_int_distribution<int> distribution(0, numberOfUnvisitedNeighbors - 1);
		int randomNumber = distribution(generator);
		std::shared_ptr<Cell> randomCell = unvisitedNeighbors[randomNumber]; //1. Choose randomly one of the unvisited neighbours
		stack.push_back(currCell); //2. Push the current cell to the stack
		removeWall(currCell, randomCell); //3. Remove the wall between the current cell and the chosen cell
		//std::cout << "step: " << ++step << " removing wall between " << currCell->value << " and " << randomCell->value << std::endl;
		//Display::printMaze(*this); //to see how the iteration goes
		currCell = randomCell; //4. Make the chosen cell the current cell 
		currCell->isVisited = true; //and mark it as visited
	}
	else if (!stack.empty()) //2. Else if stack is not empty
	{
		currCell = stack.back();//stack[stack.size() - 1]; // 1. Pop a cell from the stack
		stack.pop_back(); // 2. Make it the current cell
	}
	return currCell;
};
