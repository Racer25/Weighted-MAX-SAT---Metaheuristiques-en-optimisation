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

AlgoRandom::AlgoRandom(int nbEvaluationMax)
{
	nombreEvaluationMax = nbEvaluationMax;
	compteurEvaluation = 0;
}

void AlgoRandom::run(Instance instance)
{
	bool stop = false;

	Solution bestSolution=generateRandomSolution(instance.getNombreVariables());
	Algo::evaluer(&bestSolution, instance);
	while (!stop)
	{
		Solution newSolution= generateRandomSolution(instance.getNombreVariables());
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
}

Solution AlgoRandom::generateRandomSolution(int nombreVariables)
{
	vector<Literal> litteraux(nombreVariables);
	int tab[2];
	tab[0] = -1;
	tab[1] = 1;
	for (size_t i = 0; i< litteraux.size(); i++)
	{
		litteraux[i].numVar = i + 1;
		int pos = rand() % 2;
		if (pos == 0)
		{
			litteraux[i].value = true;
		}
		else
		{
			litteraux[i].value = false;
		}
		litteraux[i].poidsEngendre = 0;
	}
	Solution solution(litteraux);
	return solution;
}

long int Algo::evaluer(Solution* solution, Instance instance)
{
	compteurEvaluation++;
	return (*solution).evaluerSolution(instance);
}