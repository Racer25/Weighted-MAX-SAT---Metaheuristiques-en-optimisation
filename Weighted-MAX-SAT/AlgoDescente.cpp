#include "AlgoDescente.hpp"
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

AlgoDescente::AlgoDescente(int nbEvaluationMax)
{
	nombreEvaluationMax = nbEvaluationMax;
	compteurEvaluation = 0;
}

void AlgoDescente::run(Instance instance)
{
	bool stop = false;

	Solution bestSolution = generateRandomSolution(instance.getNombreVariables());
	Algo::evaluer(&bestSolution, instance);
	while (!stop)
	{
		//Voisinage...
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
		cout << "newPerf: " << newSolution.getPerformance() << ", bestPerf: " << bestSolution.getPerformance() << endl;
		cout << "#########################################" << endl;
		bestSolution.afficherSolution();
		cout << "Avec score de: " << bestSolution.getPerformance() << endl;
		cout << "Nombre d'evaluations: " << compteurEvaluation << endl;
		cout << "#########################################" << endl;
	}
}

Solution AlgoDescente::generateRandomSolution(int nombreVariables)
{
	vector<int> valeurs(nombreVariables);
	int tab[2];
	tab[0] = -1;
	tab[1] = 1;
	for (size_t i = 0; i< valeurs.size(); i++)
	{
		int pos = rand() % 2;
		valeurs[i] = tab[pos] * (i + 1);
	}
	Solution solution(valeurs);
	return solution;
}

long int Algo::evaluer(Solution* solution, Instance instance)
{
	compteurEvaluation++;
	return (*solution).evaluerSolution(instance);
}