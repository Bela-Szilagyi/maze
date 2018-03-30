#include "Logic.h"
#include "GeneticAlgorithm.h"



void renderAll()
{

}


int main(int argc, char *args[])
{
	srand(time(NULL));
	//std::string solution = "1111000000000000000000000000000000000000000000000000000000001111";
	//GeneticAlgorithm geneticAlgorithm;
	//geneticAlgorithm.run(50, solution.size(), solution);
	
	
	Logic logic(10, 10);
	logic.run();
	
	//system("pause");
	return 0;
}

