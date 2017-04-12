# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <string>
# include <cstring>
# include <fstream>
# include <cmath>
# include <ctime>
# include <vector>
# include "Instance.hpp"
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

vector<Instance> recupererInstances()
{
	cout << "#########################################" << endl;
	cout << "Lecture des instances...." << endl;
	cout << "#########################################" << endl;
	//numéro de parcours d'instance
	//vector<Instance> instances(17);
	//int numInstances[17] = { 1, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
	//for (int i = 0; i<17; i++)
	vector<Instance> instances(17);
	int numInstances[17] = { 1, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
	for (int i = 0; i<17; i++)
	{
		string sat_file_name = string("instances/jnh") + to_string(numInstances[i]) + string(".sat");
		cout << sat_file_name << endl;
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