#define _CRT_SECURE_NO_WARNINGS

# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <string>
# include <cstring>
# include <fstream>
# include <cmath>
# include <ctime>
# include <vector>

# include "sat_io.hpp"

bool sat_data_read(string sat_file_name, vector< vector<int> > *valeursParClause, vector<int> *poids, int nombreVariables, int nombreClauses)
{
	bool error;
	ifstream input;

	error = false;

	input.open(sat_file_name.c_str());

	if (!input)
	{
		cout << "\n";
		cout << "sat - Fatal error!\n";
		cout << "  Could not open file.\n";
		exit(1);
	}

	int nombre;
	input >> nombre;//NumberVariables
	input >> nombre;//Number Clauses

	int i = 0;
	int numberOfLiteralsInThisClause;
	while (input >> numberOfLiteralsInThisClause)
	{
		int weight;
		input >> weight;
		(*poids)[i]=weight;

		vector<int> literauxClause;
		literauxClause.resize(numberOfLiteralsInThisClause);
		for (int j=0; j<numberOfLiteralsInThisClause; j++)
		{
			int literal;
			input >> literal;
			literauxClause[j]=literal;
		}
		(*valeursParClause)[i]=literauxClause;
		i++;
	}
	return error;
}

bool sat_header_read(string sat_file_name, int *nombreVariables, int *nombreClauses)
{
	bool error;
	ifstream input;

	error = false;

	input.open(sat_file_name.c_str());

	if (!input)
	{
		cout << "\n";
		cout << "sat - Fatal error!\n";
		cout << "  Could not open file.\n";
		exit(1);
	}

	input >> *nombreVariables;//NumberVariables
	input >> *nombreClauses;//Number Clauses
	return error;
}