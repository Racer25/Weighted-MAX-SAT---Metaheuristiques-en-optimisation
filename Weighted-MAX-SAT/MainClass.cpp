#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
#include <math.h>
#include <cstdlib>
#include <time.h>
#include <vector>
#include "sat_io.hpp"
#include "Instance.hpp"
#include "Solution.hpp"
#include "AlgoRandom.hpp"
#include "AlgoDescente.hpp"
#include "AlgoRS.hpp"
#include "AlgoAG.hpp"

using namespace std;

int main()
{
	srand(time(NULL));
	vector<Instance> instances_Weighted_MAX_SAT = recupererInstances();
	int nombreIterationMAX = 50;
	int nombreRepetitions = 5;
	for (size_t i=0; i<instances_Weighted_MAX_SAT.size(); i++)
	{
		//instances_Weighted_MAX_SAT[i].afficherInstance();

		//AlgoRandom algoAlea(nombreIterationMAX, nombreRepetitions);
		//algoAlea.run(instances_Weighted_MAX_SAT[i]);

		//AlgoDescente algoDescente(nombreIterationMAX, nombreRepetitions);
		//algoDescente.run(instances_Weighted_MAX_SAT[i]);

		//AlgoRS algoRS(nombreIterationMAX, nombreRepetitions);
		//algoRS.run(instances_Weighted_MAX_SAT[i]);

		AlgoAG algoAG(nombreIterationMAX, nombreRepetitions);
		algoAG.run(instances_Weighted_MAX_SAT[i]);
	}
	
	
	system("pause");
    return 0;
}