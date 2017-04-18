#ifndef DEF_H_ALGOAG
#define DEF_H_ALGOAG
#include "Algo.hpp" // A inclure pour pouvoir en hériter !
using namespace std;

class AlgoAG : public Algo
{
public:
	AlgoAG(int nbEvaluationMax, int nbRepetitions);
	void run(Instance instance);
	vector<Solution> generateRandomPopulation(int taillePopulation, int nombreVariables);
	void evaluerPopulation(vector<Solution> *solutions, Instance instance);
	Solution getBestSolutionInPopulation(vector<Solution> population);
	long int getSommePerformances(vector<Solution> population);
	Solution selectionParent(vector<Solution> population); //Selectionne un parent allant se reproduire
	Solution selectionParentRang(vector<Solution> population); //Selectionne un parent allant se reproduire
	Solution AlgoAG::reproductionBinaire(Solution parent1, Solution parent2);
	Solution reproduction(Solution parent1, Solution parent2);//Produit un enfant à partir de 2 parents
	void mutation(Solution* solution); //Applique des mutations au litteraux d'une population (enfants + population OU Parents)
	vector<Solution> remplacement(vector<Solution> parents, vector<Solution> enfants);//Prends les enfants et les parents et selectionne les survivants
	vector<Solution> remplacementRang(vector<Solution> parents, vector<Solution> enfants);//Prends les enfants et les parents et selectionne les survivants

	vector<Solution> trierPopulation(vector<Solution> population);
};
#endif