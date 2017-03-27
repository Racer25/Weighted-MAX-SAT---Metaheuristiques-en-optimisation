#include "AlgoRS.hpp"
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

AlgoRS::AlgoRS(int nbEvaluationMax)
{
	nombreEvaluationMax = nbEvaluationMax;
	compteurEvaluation = 0;
}

void AlgoRS::run(Instance instance)
{
	bool stop = false;

	//Initialisation
	Solution uneSolution= generateRandomSolution(instance.getNombreVariables());
	Solution bestSolution = uneSolution;
	evaluer(&bestSolution, instance);
	double temperatureIni = 100;
	double temperature = temperatureIni;

	while (!stop)
	{
		for (int dureeTemperature =0; dureeTemperature< 10; dureeTemperature++)
		{
			//On prélève 1 voisin
			Solution newSolution = trouverVoisin(uneSolution);

			evaluer(&newSolution, instance);
			if (newSolution.getPerformance() > uneSolution.getPerformance())
			{
				uneSolution = newSolution;
				if (uneSolution.getPerformance() > bestSolution.getPerformance())
				{
					bestSolution = uneSolution;
				}

			}
			else
			{
				double random = rand() / RAND_MAX;
				if (random < exp(-(newSolution.getPerformance() - uneSolution.getPerformance()) / temperature))
				{
					uneSolution = newSolution;
				}
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
		

		temperature *= 0.9;

		if (compteurEvaluation > nombreEvaluationMax)
		{
			stop = true;
		}
	}
}

Solution AlgoRS::generateRandomSolution(int nombreVariables)
{
	vector<Literal> litteraux(nombreVariables);
	int tab[2];
	tab[0] = -1;
	tab[1] = 1;
	for (size_t i = 0; i< litteraux.size(); i++)
	{
		litteraux[i].numVar = i + 1;
		int pos = rand() % 2;
		if (i == 0)
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

long int AlgoRS::evaluer(Solution* solution, Instance instance)
{
	compteurEvaluation++;
	return (*solution).evaluerSolution(instance);
}

Solution AlgoRS::trouverVoisin(Solution solution)
{
	solution.trierLiteralsParPoidsEngendre();

	Solution voisin(solution);

	//Etablissons les probabilité cumulées dêtre selectionné
	vector<double> probaCumulees(voisin.getLiterals().size());
	double somme = voisin.getSommePoids();
	probaCumulees[0] = ((double)voisin.getLiterals()[0].poidsEngendre) / (double)somme;
	for (size_t i = 1; i< probaCumulees.size(); i++)
	{
		probaCumulees[i] = probaCumulees[i - 1] + ((double)voisin.getLiterals()[i].poidsEngendre) / (double)somme;
	}

	//On tire un double aléatoire entre 0 et 1
	double random = (double)rand() / (double)RAND_MAX;

	//Position of the literal to change
	int pos = 0;
	while (random > probaCumulees[pos])
	{
		pos++;
	}

	vector<Literal> litterauxVoisins = voisin.getLiterals();
	//Literal to change
	Literal newLiteral = solution.getLiterals()[pos];
	//We change (oppose) the value of the literal
	newLiteral.value = !newLiteral.value;
	//We set the value
	voisin.setLiteral(pos, newLiteral);
	return voisin;
}