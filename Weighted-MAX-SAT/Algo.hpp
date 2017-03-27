#ifndef DEF_H_ALGO
#define DEF_H_ALGO
#include "Solution.hpp"
#include "Instance.hpp"

class Algo 
{
	public:
		virtual void run(Instance instance) = 0;
		long int evaluer(Solution* solution, Instance instance);
		Solution generateRandomSolution(int nombreVariables);
	protected:
		int compteurEvaluation;
		int nombreEvaluationMax;

};
#endif