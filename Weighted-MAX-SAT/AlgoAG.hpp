#ifndef DEF_H_ALGOAG
#define DEF_H_ALGOAG
#include "Algo.hpp" // A inclure pour pouvoir en hériter !
using namespace std;

class AlgoAG : public Algo
{
public:
	AlgoAG(int nbEvaluationMax);
	void run(Instance instance);
	vector<Solution> generateRandomPopulation(int taillePopulation, int nombreVariables);
	void evaluerPopulation(vector<Solution*> solutions, Instance instance);
	Solution getBestSolutionInPopulation(vector<Solution> population);
	vector<Solution> selectionParents(vector<Solution> population); //Selectionne les parents allant se reproduire
	vector<Solution> croisement(vector<Solution> parents); //Créer les enfants des parents
	void mutation(vector<Solution*> solutions); //Applique des mutations au litteraux d'une population (enfants + population OU Parents)
	vector<Solution> remplacement(vector<Solution> population);//Prends une population de taille trop grande et la réduit aux nombres d'individus fixés (50?)

	vector<Solution> pointeursVersValeurs(vector<Solution*> populationPointeurs);
	vector<Solution*> valeursVersPointeurs(vector<Solution> population);
};
#endif