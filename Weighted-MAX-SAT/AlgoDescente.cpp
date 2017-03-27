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
		Solution newSolution = trouverVoisin(bestSolution);

		Algo::evaluer(&newSolution, instance);
		if (newSolution.getPerformance() > bestSolution.getPerformance())
		{
			bestSolution = newSolution;
		}

		if (compteurEvaluation > nombreEvaluationMax)
		{
			stop = true;
		}
		//newSolution.trierValeurs();
		newSolution.afficherSolution(false);
		cout << "newPerf: " << newSolution.getPerformance() << ", bestPerf: " << bestSolution.getPerformance() << endl;
		cout << "#########################################" << endl;
		bestSolution.afficherSolution(false);
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

long int AlgoDescente::evaluer(Solution* solution, Instance instance)
{
	compteurEvaluation++;
	return (*solution).evaluerSolution(instance);
}

Solution AlgoDescente::trouverVoisin(Solution solution)
{
	solution.trierValeursParPoidsEngendre();
	Solution voisin(solution);
	vector<int> valeursVoisins = voisin.getValeurs();
	//On va changer le signe (On applique un NON) d'une des 10 pires valeurs dans la solution
	int pos = rand() % 10;
	cout << "val passe de " << valeursVoisins[pos] << " à " << valeursVoisins[pos] * -1 << endl;
	voisin.setValeur(pos, valeursVoisins[pos]*-1);
	return voisin;
}