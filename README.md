A maze generator and solver program written in C++.
Graphics: SDL2 library
Maze type:
Dimension: 2D
Hyperdimension: Non-hypermaze
Topology: Normal
Tesselation: Orthogonal
Routing: First create a perfect maze and then delete some (dead ends only? Or any??) walls to make it imperfect (i.e. it has multiple solutions)
Texture: ? = Algorithm dependent
Focus: ? = Algorithm dependent
Creation algorithm:
	
First create a perfect maze and then delete some (dead ends only? Or any??) walls to make it imperfect (i.e. it has multiple solutions) - to create a maze which contains circles so different AI behaviours can be compared more easily than in the case of a perfect maze where only one solution exists.
Solving algorithms: 
	A* algorithm
Genetic algorithm 
(seed - random population, weed - fitness function, breed - crossover, mutate)
	Trémaux algorithm
