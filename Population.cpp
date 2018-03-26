#include <iostream>
#include "Population.h"



Population::Population(int populationSize, bool initialise) : populationSize(populationSize)
{
	if (initialise)
	{
		for (int i = 0; i < size(); ++i)
		{
			std::cout << "create individula nr " << i << std::endl;
		}
	}
}


Population::~Population()
{
}
