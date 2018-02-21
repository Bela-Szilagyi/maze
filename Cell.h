#pragma once

#include <memory>
#include <vector>

enum Walls
{
	north,
	east,
	south,
	west
};

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
	bool isPopped = false;
	bool isInAStarPath = false;
	bool isMarkedByTremaux = false;
	int isInTremauxPath = 0;
	std::vector<std::shared_ptr<Cell>> availableNeighbors;
	int availableNeighborCnt = 0;

	int numOfInnerWalls();
	int numOfAllWalls();
	void getInnerWalls(std::vector<Walls>& walls);
	unsigned int col;
	unsigned int row;
	unsigned int fScore;
	unsigned int gScore;
};
