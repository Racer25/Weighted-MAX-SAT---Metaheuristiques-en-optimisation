#include "AlgoRandom.hpp"
#include <cstdio>
#include <cstdlib> 
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>  
#include <cmath>
#include <vector>
using namespace std;

AlgoRandom::AlgoRandom(int nbEvaluationMax, int nbRepetitions)
{
	nombreEvaluationMax = nbEvaluationMax;
	nombreRepetitions = nbRepetitions;
	compteurEvaluation = 0;
}

void AlgoRandom::run(Instance instance)
{
	for (int repetition=1; repetition<=nombreRepetitions; repetition++)
	{
		compteurEvaluation = 0;
		bool stop = false;

		Solution bestSolution = generateRandomSolution(instance.getNombreVariables());
		Algo::evaluer(&bestSolution, instance);
		while (!stop)
		{
			Solution newSolution = generateRandomSolution(instance.getNombreVariables());
			Algo::evaluer(&newSolution, instance);
			if (newSolution.getPerformance() > bestSolution.getPerformance())
			{
				bestSolution = newSolution;
			}

			if (compteurEvaluation > nombreEvaluationMax)
			{
				stop = true;
			}
			cout << "#########################################" << endl;
			cout << "#########################################" << endl;
			bestSolution.afficherSolution(false);
			cout << "bestPerf: " << bestSolution.getPerformance() << endl;
			cout << "#########################################" << endl;
			newSolution.afficherSolution(false);
			cout << "newPerf: " << newSolution.getPerformance() << endl;
			cout << "Nombre d'evaluations: " << compteurEvaluation << endl;
			cout << "#########################################" << endl;
			cout << "#########################################" << endl;
		}
		Algo::extractSolutionToFile("AlgoRandom", repetition, bestSolution, instance);
	}
}