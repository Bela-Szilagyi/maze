#include "Cell.h"


//TODO refactor to give back num of all walls instead of inner walls
int Cell::numOfInnerWalls()
{
	int result = 0;
	if (nNeighbor && nWall) ++result;
	if (eNeighbor && eWall) ++result;
	if (sNeighbor && sWall) ++result;
	if (wNeighbor && wWall) ++result;
	return result;
}

int Cell::numOfAllWalls()
{
	int result = 0;
	if (nWall) ++result;
	if (eWall) ++result;
	if (sWall) ++result;
	if (wWall) ++result;
	return result;
}

void Cell::getInnerWalls(std::vector<Walls>& walls)
{
	if (nNeighbor && nWall) walls.push_back(Walls::north);
	if (eNeighbor && eWall) walls.push_back(Walls::east);
	if (sNeighbor && sWall) walls.push_back(Walls::south);
	if (wNeighbor && wWall) walls.push_back(Walls::west);
}