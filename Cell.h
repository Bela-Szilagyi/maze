#pragma once

#include <memory>

class Cell
{
public:
	Cell(int v) : value(v) {};
	bool nWall = true;
	bool eWall = true;
	bool sWall = true;
	bool wWall = true;
	std::shared_ptr<Cell> nNeighbor = nullptr;
	std::shared_ptr<Cell> eNeighbor = nullptr;
	std::shared_ptr<Cell> sNeighbor = nullptr;
	std::shared_ptr<Cell> wNeighbor = nullptr;
	//TODO value private 
	int value;
	bool isVisited = false;
};
