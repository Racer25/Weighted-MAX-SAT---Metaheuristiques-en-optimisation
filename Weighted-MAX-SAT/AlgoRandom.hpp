#ifndef DEF_H_ALGORANDOM
#define DEF_H_ALGORANDOM
#include "Algo.hpp" // A inclure pour pouvoir en h�riter !

class AlgoRandom : public Algo
{
	public:
		AlgoRandom(int nbEvaluationMax);
		void run(Instance instance);
};
#endif