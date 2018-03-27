#include "Logic.h"
#include "GeneticAlgorithm.h"



void renderAll()
{

}


int main(int argc, char *args[])
{
	srand(time(NULL));
	std::string solution = "1111111111";
	GeneticAlgorithm geneticAlgorithm;
	geneticAlgorithm.run(12, 10, solution);
	
	
	//Logic logic(60, 60);
	//logic.run();
	
	system("pause");
	return 0;
}

