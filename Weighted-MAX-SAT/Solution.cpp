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

Solution::Solution(int nombreLitteraux)
{
	vector<Literal> lits(nombreLitteraux);
	litteraux = lits;
	performance = 0;
}

Solution::Solution(vector<Literal> lits)
{
	litteraux = lits;
	performance = 0;
	vector<Literal> pds(lits);
}

vector<Literal> Solution::getLiterals()
{
	return litteraux;
}

void Solution::setLiterals(std::vector<Literal> lits)
{
	litteraux = lits;
}

void Solution::setLiteral(int pos, Literal lit)
{
	litteraux[pos] = lit;
}

long int Solution::getPerformance()
{
	return performance;
}

void Solution::afficherSolution(bool avecPoids)
{
	if (avecPoids)
	{
		for (size_t i = 0; i<litteraux.size(); i++)
		{
			cout << litteraux[i].numVar << ":" << std::boolalpha << litteraux[i].value << ":" << litteraux[i].poidsEngendre << "  ";
		}
		cout << "\n";
	}
	else
	{
		for (size_t i = 0; i<litteraux.size(); i++)
		{
			cout << litteraux[i].numVar << ":" << std::boolalpha<< litteraux[i].value << "  ";
		}
		cout << "\n";
	}
	
}

long int Solution::evaluerSolution(Instance instance)
{
	//On trie par numVar
	trierLiteralsParNumVar();
	long int res = 0;
	vector < vector<int> > valeursParClause = instance.getValeursParClause();
	//On parcourt les clauses
	for (size_t i = 0; i<valeursParClause.size(); i++)
	{
		bool clauseValide = false;
		//on parcourt les valeurs de la clause courante
		for (size_t j = 0; j<valeursParClause[i].size(); j++)
		{
			int literal = valeursParClause[i][j];
			if (abs(literal) == litteraux[abs(literal)-1].numVar && ((literal < 0 && !litteraux[abs(literal) - 1].value) || (literal > 0 && litteraux[abs(literal) - 1].value)))
			{
				clauseValide = true;
				litteraux[abs(literal) - 1].poidsEngendre += instance.getPoids()[i];
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

bool compare(Literal i, Literal j)
{
	return i.numVar < j.numVar;
}

void Solution::trierLiteralsParNumVar()
{
	sort(litteraux.begin(), litteraux.end(), compare);
}

void Solution::trierLiteralsParPoidsEngendre()
{
	vector<Literal> literalTries(litteraux.size());
	vector<Literal> copyLiterals(litteraux);
	for (size_t i = 0; i<literalTries.size(); i++)
	{
		//Trouver mini
		Literal literalMin = copyLiterals[0];
		int posMin = 0;
		int pos = 0;
		while (pos < (int)copyLiterals.size())
		{
			if (copyLiterals[pos].poidsEngendre < copyLiterals[posMin].poidsEngendre)
			{
				literalMin = copyLiterals[pos];
				posMin = pos;
			}
			pos++;
		}
		//Affectation
		literalTries[i] = literalMin;

		copyLiterals.erase(copyLiterals.begin() + posMin);
	}
	litteraux = literalTries;
}

int Solution::getSommePoids()
{
	int sommePoids= 0;
	for (size_t i = 1; i<litteraux.size(); i++)
	{
		sommePoids += litteraux[i].poidsEngendre;
	}
	return sommePoids;
}

string Solution::toString()
{
	string maString = "0=Faux, 1=Vrai\n\n";
	for (size_t i = 0; i<litteraux.size(); i++)
	{
		maString += "x"+to_string(litteraux[i].numVar) + ":" + to_string(litteraux[i].value) + "\t";
		if ((i+1)%15==0)
		{
			maString += "\n";
		}
	}
	maString += "\n\nPerformance: " + to_string(performance);
	
	return maString;
}
