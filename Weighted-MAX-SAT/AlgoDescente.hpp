#ifndef DEF_H_ALGODESCENTE
#define DEF_H_ALGODESCENTE
#include "Algo.hpp" // A inclure pour pouvoir en hériter !

class AlgoDescente : public Algo
{
	public:
		AlgoDescente(int nbEvaluationMax, int nbRepetitions);
		void run(Instance instance);
		Solution trouverVoisin(Solution solutiion);
};
#endif