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

	int minDistanceFromGoal = 1000;

	static int getMinDistanceFromGoal(Individual individual) { return individual.minDistanceFromGoal; }
	static void setMinDistanceFromGoal(Individual individual, int value) { individual.minDistanceFromGoal = value; }
	
	void generateIndividual();
	double getFitness(Maze &maze);
	//static void setDefaultGeneLength(int length);
	int size() { return genes.size(); }
	int getGene(int index) { return genes[index]; }
	void setGene(int index, int value);
	std::string to_string_();
	std::string to_string_h();
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
	
	double getFitness(Individual individual, Maze &maze);
	double getMaxFitness();
	std::shared_ptr<Cell> moveToNextCell(std::shared_ptr<Cell> currentCell, std::string currentDirerction);
	double calcFitness(int minDist, std::shared_ptr<Cell> currentCell, std::shared_ptr<Cell> goal, std::shared_ptr<Cell> start, int nSteps, bool containsVisitedCell);

private:
	//static int defaultGeneLength;
	double fitness = 0;
	int geneLength;
	//int genes[defaultGeneLength];
	std::vector<int> genes;
};
