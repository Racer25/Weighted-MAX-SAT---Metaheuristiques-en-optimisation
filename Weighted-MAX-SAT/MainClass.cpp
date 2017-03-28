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

using namespace std;

int main()
{
	srand(time(NULL));
	vector<Instance> instances_Weighted_MAX_SAT = recupererInstances();

	for (size_t i=0; i<instances_Weighted_MAX_SAT.size(); i++)
	{
		//instances_Weighted_MAX_SAT[i].afficherInstance();

		//AlgoRandom algoAlea(10000);
		//algoAlea.run(instances_Weighted_MAX_SAT[i]);

		//AlgoDescente algoDescente(10000);
		//algoDescente.run(instances_Weighted_MAX_SAT[i]);

		AlgoRS algoRS(10000);
		algoRS.run(instances_Weighted_MAX_SAT[i]);
	}
	
	
	system("pause");
    return 0;
}