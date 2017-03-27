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
	evaluer(&bestSolution, instance);
	while (!stop)
	{
		//On prélève 1 voisin
		Solution newSolution = trouverVoisin(bestSolution);

		evaluer(&newSolution, instance);
		if (newSolution.getPerformance() > bestSolution.getPerformance())
		{
			bestSolution = newSolution;
		}

		if (compteurEvaluation > nombreEvaluationMax)
		{
			stop = true;
		}
		//newSolution.trierValeurs();
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

Solution AlgoDescente::generateRandomSolution(int nombreVariables)
{
	vector<Literal> litteraux(nombreVariables);
	int tab[2];
	tab[0] = -1;
	tab[1] = 1;
	for (size_t i = 0; i< litteraux.size(); i++)
	{
		litteraux[i].numVar = i+1;
		int pos = rand() % 2;
		if (i==0)
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

long int AlgoDescente::evaluer(Solution* solution, Instance instance)
{
	compteurEvaluation++;
	return (*solution).evaluerSolution(instance);
}

Solution AlgoDescente::trouverVoisin(Solution solution)
{
	solution.trierLiteralsParPoidsEngendre();

	Solution voisin(solution);

	//Etablissons les probabilité cumulées dêtre selectionné
	vector<double> probaCumulees(voisin.getLiterals().size());
	double somme = voisin.getSommePoids();
	probaCumulees[0] = ((double)voisin.getLiterals()[0].poidsEngendre) / (double)somme;
	for (size_t i = 1; i< probaCumulees.size(); i++)
	{
		probaCumulees[i]= probaCumulees[i-1]+((double)voisin.getLiterals()[i].poidsEngendre)/(double)somme;
	}

	//On tire un double aléatoire entre 0 et 1
	double random = (double)rand()/(double) RAND_MAX;

	//Position of the literal to change
	int pos = 0;
	while (random > probaCumulees[pos])
	{
		pos++;
	}

	vector<Literal> litterauxVoisins = voisin.getLiterals();
	//Literal to change
	Literal newLiteral=solution.getLiterals()[pos];
	//We change (oppose) the value of the literal
	newLiteral.value = !newLiteral.value;
	//We set the value
	voisin.setLiteral(pos, newLiteral);
	return voisin;
}