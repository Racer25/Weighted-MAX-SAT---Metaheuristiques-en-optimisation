#ifndef DEF_H_ALGORS
#define DEF_H_ALGORS
#include "Algo.hpp" // A inclure pour pouvoir en hériter !

class AlgoRS : public Algo
{
public:
	AlgoRS(int nbEvaluationMax,int nbRepetitions);
	void run(Instance instance);
	Solution trouverVoisin(Solution solutiion);
};
#endif