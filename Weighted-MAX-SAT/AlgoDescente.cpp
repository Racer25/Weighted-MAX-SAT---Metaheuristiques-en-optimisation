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

AlgoDescente::AlgoDescente(int nbEvaluationMax, int nbRepetitions)
{
	nombreEvaluationMax = nbEvaluationMax;
	nombreRepetitions = nbRepetitions;
	compteurEvaluation = 0;
	performanceMoyenneFinale = 0.0;
}

void AlgoDescente::run(Instance instance)
{
	for (int repetition = 1; repetition <= nombreRepetitions; repetition++)
	{
		cout << "Instance:" << instance.getNom() << endl;
		cout << "AlgoDescente--" << "Repetition " << repetition << "--NbEvaluationMax=" << nombreEvaluationMax << endl;

		compteurEvaluation = 0;
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
			/*
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
			*/
		}
		cout << "#########################################" << endl;
		cout << "Meilleure Performance de la repetition: " << bestSolution.getPerformance() << endl;
		cout << "#########################################\n" << endl;
		performanceMoyenneFinale += (double)bestSolution.getPerformance() / (double)nombreRepetitions;
		Algo::extractSolutionToFile("AlgoDescente", repetition, bestSolution, instance);
	}
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