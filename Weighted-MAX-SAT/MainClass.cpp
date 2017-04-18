#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
#include <math.h>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "sat_io.hpp"
#include "Instance.hpp"
#include "Solution.hpp"
#include "AlgoRandom.hpp"
#include "AlgoDescente.hpp"
#include "AlgoRS.hpp"
#include "AlgoAG.hpp"

using namespace std;

void extractToFile(Instance instance, AlgoRandom algoRandom, AlgoDescente algoDescente, AlgoRS algoRS, AlgoAG algoAG);

int main()
{
	remove("results/resultsAverage.txt");
	srand(time(NULL));
	vector<Instance> instances_Weighted_MAX_SAT = recupererInstances();
	int nombreIterationMAX = 4000;
	int nombreRepetitions = 3;
	for (size_t i=0; i<instances_Weighted_MAX_SAT.size(); i++)
	{
		cout << "#########################################" << endl;
		cout << "Application des algorithmes...." << endl;
		cout << "#########################################" << endl;
		//instances_Weighted_MAX_SAT[i].afficherInstance();

		AlgoRandom algoAlea(nombreIterationMAX, nombreRepetitions);
		algoAlea.run(instances_Weighted_MAX_SAT[i]);

		AlgoDescente algoDescente(nombreIterationMAX, nombreRepetitions);
		algoDescente.run(instances_Weighted_MAX_SAT[i]);

		AlgoAG algoAG(nombreIterationMAX, nombreRepetitions);
		AlgoAG.run(instances_Weighted_MAX_SAT[i]);

		AlgoRS algoRS(nombreIterationMAX, nombreRepetitions);
		algoRS.run(instances_Weighted_MAX_SAT[i]);

		extractToFile(instances_Weighted_MAX_SAT[i], algoAlea, algoDescente, algoRS, algoAG);
	}
	
	
	system("pause");
    return 0;
}

void extractToFile(Instance instance, AlgoRandom algoRandom, AlgoDescente algoDescente, AlgoRS algoRS, AlgoAG algoAG)
{
	ofstream myfile;
	myfile.open("results/resultsAverage.txt", fstream::app);
	string instanceName = instance.getNom().substr(10, instance.getNom().length() - 10);

	myfile << instanceName + "| | |";
	myfile << "AlgoRandom:"+to_string(algoRandom.getPerformanceMoyenneFinale())+"\t";
	myfile << "AlgoDescente:" + to_string(algoDescente.getPerformanceMoyenneFinale()) + "\t";
	myfile << "AlgoRS:" + to_string(algoRS.getPerformanceMoyenneFinale()) + "\t";
	myfile << "AlgoAG:" + to_string(algoAG.getPerformanceMoyenneFinale()) + "\n";

	myfile.close();
}