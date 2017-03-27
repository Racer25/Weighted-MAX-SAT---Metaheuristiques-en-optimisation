#include "Solution.hpp"
#include <cstdio>
#include <cstdlib> 
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>  
#include <cmath>

using namespace std;

Solution::Solution()
{

}

Solution::Solution(vector<int> val)
{
	valeurs = val;
	performance = 0;
}

vector<int> Solution::getValeurs()
{
	return valeurs;
}

long int Solution::getPerformance()
{
	return performance;
}

void Solution::afficherSolution()
{
	for (size_t i = 0; i<valeurs.size(); i++)
	{
		cout << valeurs[i] << "  ";
	}
	cout << "\n";
}

long int Solution::evaluerSolution(Instance instance)
{
	long int res = 0;
	vector < vector<int> > valeursParClause = instance.getValeursParClause();
	for (size_t i = 0; i<valeursParClause.size(); i++)
	{
		//cout << "Clause: " << i << endl;
		bool clauseValide = false;
		for (size_t j = 0; j<valeursParClause[i].size(); j++)
		{
			//cout << "Boucle2" << endl;
			int literal = valeursParClause[i][j];
			if (literal == valeurs[abs(literal) - 1])
			{
				clauseValide = true;
			}
		}
		if (clauseValide)
		{
			res += instance.getPoids()[i];
		}
	}
	performance = res;
	return res;
}