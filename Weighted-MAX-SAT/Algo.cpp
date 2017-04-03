#include "Algo.hpp"
#include <cstdio>
#include <cstdlib> 
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>  
#include <cmath>
#include <vector>
#include <random>
#include <iostream>
#include <fstream>
using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> distributionUniforme(0, 1);

Solution Algo::generateRandomSolution(int nombreVariables)
{
	vector<Literal> litteraux(nombreVariables);
	int tab[2];
	tab[0] = -1;
	tab[1] = 1;
	for (size_t i = 0; i< litteraux.size(); i++)
	{
		litteraux[i].numVar = i + 1;
		//int pos = rand() % 2;
		int pos= distributionUniforme(gen);
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

void Algo::extractSolutionToFile(string algoName, int repetitionNum, Solution solution, Instance instance)
{
	ofstream myfile;
	string instanceName = instance.getNom().substr(10, instance.getNom().length()-10);
	string fileName = "results/"+instanceName+"/result_"+algoName+"_repetition"+to_string(repetitionNum)+"_"+instanceName +".txt";
	myfile.open(fileName);

	myfile << "Instance: " + instanceName+"\n";
	myfile << solution.toString();

	myfile << "\nNombre d'évaluations: "+to_string(compteurEvaluation);
	myfile.close();
}
