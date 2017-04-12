#ifndef DEF_H_ALGO
#define DEF_H_ALGO
#include "Solution.hpp"
#include "Instance.hpp"
#include <string>


class Algo 
{
	public:
		virtual void run(Instance instance) = 0;//Retourne la performance moyenne
		Solution generateRandomSolution(int nombreVariables);
		long int evaluer(Solution* solution, Instance instance);
		void extractSolutionToFile(std::string algoName, int repetitionNum, Solution solution, Instance instance);
		double getPerformanceMoyenneFinale();
	protected:
		int compteurEvaluation;
		int nombreEvaluationMax;
		int nombreRepetitions;
		double performanceMoyenneFinale;
};
#endif