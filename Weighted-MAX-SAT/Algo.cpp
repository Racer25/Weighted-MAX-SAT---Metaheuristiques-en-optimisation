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

Solution Algo::generateRandomSolution(int nombreVariables)
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

long int Algo::evaluer(Solution* solution, Instance instance)
{
	compteurEvaluation++;
	return (*solution).evaluerSolution(instance);
}