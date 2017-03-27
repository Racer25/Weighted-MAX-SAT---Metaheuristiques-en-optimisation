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
using namespace std;

long int Algo::evaluer(Solution* solution, Instance instance)
{
	compteurEvaluation++;
	return (*solution).evaluerSolution(instance);
}

Solution Algo::generateRandomSolution(int nombreVariables)
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