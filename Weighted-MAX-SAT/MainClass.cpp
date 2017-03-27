#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
#include <math.h>
#include <cstdlib>
#include <time.h>
#include <vector>
#include "sat_io.hpp"
#include "Instance.hpp"
#include "Solution.hpp"
#include "functions.hpp"
#include "AlgoRandom.hpp"
#include "AlgoDescente.hpp"
#include "AlgoRS.hpp"

using namespace std;

int main()
{
	srand(time(NULL));
	vector<Instance> instances_Weighted_MAX_SAT = recupererInstances();

	for (size_t i=0; i<instances_Weighted_MAX_SAT.size(); i++)
	{
		//instances_Weighted_MAX_SAT[i].afficherInstance();

		//AlgoRandom algoAlea(10000);
		//algoAlea.run(instances_Weighted_MAX_SAT[i]);

		//AlgoDescente algoDescente(10000);
		//algoDescente.run(instances_Weighted_MAX_SAT[i]);

		AlgoRS algoRS(10000);
		algoRS.run(instances_Weighted_MAX_SAT[i]);
	}
	
	
	system("pause");
    return 0;
}

Solution generateRandomSolution(int nombreVariables)
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

void afficherSolution(vector<int> solution)
{
	for (size_t i=0; i<solution.size(); i++)
	{
		cout << solution[i] << "  ";
	}
	cout << "\n";
}

vector<Instance> recupererInstances()
{
	//numéro de parcours d'instance
	//vector<Instance> instances(17);
	//int numInstances[17] = { 1, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
	//for (int i = 0; i<17; i++)
	vector<Instance> instances(1);
	int numInstances[1] = { 1 };
	for (int i = 0; i<1; i++)
	{
		string sat_file_name = string("instances/jnh") + to_string(numInstances[i]) + string(".sat");

		int nombreVariables;
		int nombreClauses;
		vector< vector<int> > valeursParClause;
		vector<int> poids;

		sat_header_read(sat_file_name, &nombreVariables, &nombreClauses);

		valeursParClause.resize(nombreClauses);
		poids.resize(nombreClauses);

		sat_data_read(sat_file_name, &valeursParClause, &poids, nombreVariables, nombreClauses);

		//Construction de la structure d'instance
		Instance instance(sat_file_name, nombreVariables, nombreClauses, poids, valeursParClause);
		instances[i] = instance;
	}

	return instances;
}

