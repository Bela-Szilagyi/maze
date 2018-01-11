#include<iostream>
#include<vector>
#include<random>
#include<memory>


class Cell
{
public:
	Cell(int v)  : value(v) {};
	bool nWall = true;
	bool eWall = true;
	bool sWall = true;
	bool wWall = true;
	std::shared_ptr<Cell> nNeighbor = nullptr;
	std::shared_ptr<Cell> eNeighbor = nullptr;
	std::shared_ptr<Cell> sNeighbor = nullptr;
	std::shared_ptr<Cell> wNeighbor = nullptr;
	int value;
	bool isVisited = false;
};

class Maze
{
public:
	Maze(int, int);
	std::shared_ptr<Cell> root;
	void carve();
private:
	void removeWall(std::shared_ptr<Cell>& currCell, std::shared_ptr<Cell>& neighbor);
	void getUnvisitedNeighbors(std::shared_ptr<Cell> &currCell, std::vector<std::shared_ptr<Cell>> &unvisitedNeighbors);
};

void printMaze(Maze);

Maze::Maze(int rows, int columns)
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
		if ( (i+1)%columns != 0 ) cells[i]->eNeighbor = cells[i + 1];
		//sNeighbor
		if (i < (rows - 1) * columns) cells[i]->sNeighbor = cells[i + columns];
		//wNeighbor
		if ( i % columns != 0) cells[i]->wNeighbor = cells[i - 1];
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

void Maze::carve() //Recursive backtracker
{
	// for randomization
	std::random_device device;
	std::mt19937 generator(device());

	std::shared_ptr<Cell> currCell = root; //1. Make the initial cell the current cell 
	currCell->isVisited = true;	//and mark it as visited
	std::vector< std::shared_ptr<Cell> > unvisitedNeighbors;
	std::vector< std::shared_ptr<Cell> > stack;
	int step = 0;
	do
	{
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
			std::cout << "step: " << ++step << " removing fall between " << currCell->value << " and " << randomCell->value << std::endl;
			printMaze(*this); //to see how the iteration goes
			currCell = randomCell; //4. Make the chosen cell the current cell 
			currCell->isVisited = true; //and mark it as visited
		}
		else if ( !stack.empty() ) //2. Else if stack is not empty
		{
			currCell = stack[stack.size() - 1]; // 1. Pop a cell from the stack
			stack.pop_back(); // 2. Make it the current cell
		}
	} while (!unvisitedNeighbors.empty() || !stack.empty()); //2. While there are unvisited cells
};

void printMazeValues(Maze m)
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

void printMaze(Maze m)
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

int main()
{
	Maze maze(4, 3); //Maze maze(10, 36);
	printMazeValues(maze);
	printMaze(maze);
	maze.carve();
	system("pause");
	return 0;
}