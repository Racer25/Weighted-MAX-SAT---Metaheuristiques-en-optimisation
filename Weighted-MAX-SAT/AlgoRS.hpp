#ifndef DEF_H_ALGORS
#define DEF_H_ALGORS
#include "Algo.hpp" // A inclure pour pouvoir en hériter !

class AlgoRS : public Algo
{
public:
	AlgoRS(int nbEvaluationMax);
	void run(Instance instance);
	Solution generateRandomSolution(int nombreVariables);
	long int evaluer(Solution* solution, Instance instance);
	Solution trouverVoisin(Solution solutiion);
};
#endif