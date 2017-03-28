#include "AlgoAG.hpp"
#include <cstdio>
#include <cstdlib> 
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>  
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

AlgoAG::AlgoAG(int nbEvaluationMax)
{
	nombreEvaluationMax = nbEvaluationMax;
	compteurEvaluation = 0;
}

void AlgoAG::run(Instance instance)
{
	bool stop = false;
	//Initialisation
	//Création d'une population
	int taillePopulation = 50;
	vector<Solution> population = generateRandomPopulation(50, instance.getNombreVariables);
	//Evaluation de la population
	evaluerPopulation(valeursVersPointeurs(population), instance);
	//Initialisation bestSolution
	Solution bestSolution = getBestSolutionInPopulation(population);
	int numGeneration = 0;
	while (!stop)
	{
		numGeneration++;

		if (compteurEvaluation > nombreEvaluationMax)
		{
			stop = true;
		}

		cout << "#########################################" << endl;
		cout << "#########################################" << endl;
		bestSolution.afficherSolution(false);
		cout << "bestPerf: " << bestSolution.getPerformance() << endl;
		cout << "Nombre d'evaluations: " << compteurEvaluation << endl;
		cout << "#########################################" << endl;
		cout << "#########################################" << endl;
	}
}

vector<Solution> AlgoAG::generateRandomPopulation(int taillePopulation, int nombreVariables)
{
	vector<Solution> pop(taillePopulation);
	for (size_t i = 0; i < pop.size(); i++)
	{
		pop[i] = generateRandomSolution(nombreVariables);
	}
}

void AlgoAG::evaluerPopulation(vector<Solution*> population, Instance instance)
{
	compteurEvaluation+= population.size();
	for (size_t i=0; i< population.size; i++)
	{
		(*(population[i])).evaluerSolution(instance);
	}
}

Solution AlgoAG::getBestSolutionInPopulation(vector<Solution> population)
{
	vector<Solution> maPop(population);
	sort(maPop.begin(), maPop.end(), compare);
	return maPop[0];
}

vector<Solution> AlgoAG::pointeursVersValeurs(vector<Solution*> populationPointeurs)
{
	vector<Solution> population(populationPointeurs.size());
	for (size_t i=0; i<population.size(); i++)
	{
		population[i] = *(populationPointeurs[i]);
	}
	return population;
}

vector<Solution*> AlgoAG::valeursVersPointeurs(vector<Solution> population)
{
	vector<Solution*> populationPointeurs(population.size());
	for (size_t i = 0; i<population.size(); i++)
	{
		populationPointeurs[i] = &(population[i]);
	}
	return populationPointeurs;
}

bool compare(Solution i, Solution j)
{
	return i.getPerformance() > j.getPerformance();
}
