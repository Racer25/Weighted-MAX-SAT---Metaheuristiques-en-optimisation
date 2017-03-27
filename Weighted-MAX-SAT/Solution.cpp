#include "Solution.hpp"
#include <cstdio>
#include <cstdlib> 
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>  
#include <cmath>
#include <algorithm>

using namespace std;

Solution::Solution()
{

}

Solution::Solution(vector<int> val)
{
	valeurs = val;
	performance = 0;
	vector<int> pds(val.size());
	poidsEngendresParLiteraux = pds;
}

vector<int> Solution::getValeurs()
{
	return valeurs;
}

void Solution::setValeurs(std::vector<int> vals)
{
	valeurs = vals;
}

void Solution::setValeur(int pos, int val)
{
	valeurs[pos] = val;
}

std::vector<int> Solution::getPoidsEngendresParLiteraux()
{
	return poidsEngendresParLiteraux;
}

long int Solution::getPerformance()
{
	return performance;
}

void Solution::afficherSolution(bool avecPoids)
{
	if (avecPoids)
	{
		for (size_t i = 0; i<valeurs.size(); i++)
		{
			cout << valeurs[i] << ":" << poidsEngendresParLiteraux[i] << "  ";
		}
		cout << "\n";
	}
	else
	{
		for (size_t i = 0; i<valeurs.size(); i++)
		{
			cout << valeurs[i] << "  ";
		}
		cout << "\n";
	}
	
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
			for (size_t k = 0; k<valeurs.size(); k++)
			{
				if (literal == valeurs[k])
				{
					clauseValide = true;
					poidsEngendresParLiteraux[k] += instance.getPoids()[i];
				}
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

bool compare(int i, int j)
{
	return abs(i) < abs(j);
}

void Solution::trierValeurs()
{
	sort(valeurs.begin(), valeurs.end(), compare);
}

void Solution::trierValeursParPoidsEngendre()
{
	sort(valeurs.begin(), valeurs.end(), compare);
	vector<int> valeursTriees(valeurs.size());
	vector<int> poidsTries(poidsEngendresParLiteraux.size());
	vector<int> copyValeurs(valeurs);
	vector<int> copyPoids(poidsEngendresParLiteraux);
	for (size_t i = 0; i<valeursTriees.size(); i++)
	{
		//Trouver mini
		int min = copyValeurs[0];
		int posMin = 0;
		int pos = 0;
		while (pos < (int)copyValeurs.size())
		{
			if (copyPoids[pos] < copyPoids[posMin])
			{
				min = copyValeurs[pos];
				posMin = pos;
			}
			pos++;
		}
		//Affectation
		valeursTriees[i] = min;
		poidsTries[i] = copyPoids[posMin];

		copyValeurs.erase(copyValeurs.begin() + posMin);
		copyPoids.erase(copyPoids.begin() + posMin);
	}
	valeurs = valeursTriees;
	poidsEngendresParLiteraux = poidsTries;
}
