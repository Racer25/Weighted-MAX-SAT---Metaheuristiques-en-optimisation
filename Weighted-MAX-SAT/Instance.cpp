#include "Instance.hpp"
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

Instance::Instance()
{

}

Instance::Instance(string nm, int nV, int nC, vector<int> pds, vector< vector<int> > vPC)
{
	nom=nm;
	nombreVariables=nV;
	nombreClauses= nC;
	poids = pds;
	valeursParClause=vPC;	// Liste de litéraux de chaque clause
}

string Instance::getNom()
{
	return nom;
}

int Instance::getNombreVariables()
{
	return nombreVariables;
}

int Instance::getNombreClauses()
{
	return nombreClauses;
}

vector<int> Instance::getPoids()
{
	return poids;
}

vector< vector<int> > Instance::getValeursParClause()
{
	return valeursParClause;
}

void Instance::afficherInstance()
{
	cout << "\n\nInstance de problème: " << endl;
	for (size_t i = 0; i<valeursParClause.size(); i++)
	{
		cout << "Clause " << i << ": ";
		cout << "| Poids: " << poids[i] << " ";
		cout << "| NombreLiteraux: : " << valeursParClause[i].size() << " |||| ";
		for (size_t j = 0; j<valeursParClause[i].size(); j++)
		{
			cout << valeursParClause[i][j] << ", ";
		}
		cout << "\n";
	}
}