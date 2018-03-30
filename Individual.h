#pragma once

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <memory>
#include "Maze.h"

class Individual
{
public:
	Individual(int geneLength);
	~Individual();
	
	void generateIndividual();
	int getFitness(Maze &maze);
	//static void setDefaultGeneLength(int length);
	int size() { return genes.size(); }
	int getGene(int index) { return genes[index]; }
	void setGene(int index, int value);
	std::string to_string_();
	std::string getGenes()
	{
		std::string result = "";
		for (int i = 0; i < genes.size(); ++i)
		{
			result += std::to_string(genes[i]);
		}
		return result;
	}

	//static?
	static std::vector<int> solution;
	static void setSolution(std::vector<int> newSolution);
	static void setSolution(std::string newSolution);
	static int getFitness(Individual individual, Maze &maze);
	static int getMaxFitness();
	static std::shared_ptr<Cell> moveToNextCell(std::shared_ptr<Cell> currentCell, std::string currentDirerction);
	static int calcFitness(std::shared_ptr<Cell> currentCell, std::shared_ptr<Cell> goal, int moveCount);

private:
	//static int defaultGeneLength;
	int fitness = 0;
	int geneLength;
	//int genes[defaultGeneLength];
	std::vector<int> genes;
};
