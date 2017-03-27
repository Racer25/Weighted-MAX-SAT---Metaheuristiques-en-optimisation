#ifndef DEF_H_ALGODESCENTE
#define DEF_H_ALGODESCENTE
#include "Algo.hpp" // A inclure pour pouvoir en hériter !

class AlgoDescente : public Algo
{
public:
	AlgoDescente(int nbEvaluationMax);
	void run(Instance instance);
	Solution generateRandomSolution(int nombreVariables);
	long int evaluer(Solution* solution, Instance instance);
};
#endif