﻿#include "Logic.h"
#include "GeneticAlgorithm.h"



void renderAll()
{

}


int main(int argc, char *args[])
{
	srand(time(NULL));
	GeneticAlgorithm geneticAlgorithm;
	geneticAlgorithm.run();
	
	
	//Logic logic(60, 60);
	//logic.run();
	
	system("pause");
	return 0;
}

