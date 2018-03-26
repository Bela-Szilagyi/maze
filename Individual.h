
class Individual
{
public:
	Individual();
	~Individual();
	
	void generateIndividual();
	int getFitness();
private:
	int fitness = 0;
};
