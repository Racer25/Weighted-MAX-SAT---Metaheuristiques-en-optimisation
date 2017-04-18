#include "AlgoAG.hpp"
#include <cstdio>
#include <cstdlib> 
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>  
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

AlgoAG::AlgoAG(int nbEvaluationMax, int nbRepetitions)
{
	nombreEvaluationMax = nbEvaluationMax;
	nombreRepetitions = nbRepetitions;
	compteurEvaluation = 0;
	performanceMoyenneFinale = 0.0;
}

void AlgoAG::run(Instance instance)
{
	for (int repetition = 1; repetition <= nombreRepetitions; repetition++)
	{
		cout << "Instance: " << instance.getNom() << endl;
		cout << "AlgoGenetique--" << "Repetition " << repetition << "--NbEvaluationMax=" << nombreEvaluationMax << endl;
		compteurEvaluation = 0;
		bool stop = false;
		//Initialisation
		int taillePopulation = 50;
		double probabiliteCroisement = 0.8;
		double probabiliteMutation = 0.2;
		int nombreEnfants = (int)(taillePopulation*probabiliteCroisement);

		//Création d'une population
		vector<Solution> population = generateRandomPopulation(50, instance.getNombreVariables());

		//Evaluation de la population
		evaluerPopulation(&population, instance);

		//Initialisation bestSolution
		Solution bestSolution = getBestSolutionInPopulation(population);

		int numGeneration = 0;
		while (!stop)
		{
			numGeneration++;
			vector<Solution> enfants(nombreEnfants);
			//cout << "DEBUT CREATION ENFANTS" << endl;
			population = trierPopulation(population);
			for (int i = 0; i<nombreEnfants; i++)
			{
				//SELECTION
				//cout << "DEBUT SELECTION" << endl;
				Solution parent1 = selectionParentRang(population);
				Solution parent2 = selectionParentRang(population);
				//cout << "Perf parent1: " << parent1.getPerformance() << endl;
				//cout << "FIN SELECTION" << endl;

				//CROISEMENT
				enfants[i] = reproduction(parent1, parent2);
				evaluer(&(enfants[i]), instance);
				//**MUTATION d'une solution
				double random = double(rand()) / double(RAND_MAX);
				if (random < probabiliteMutation)
				{
					//Vérification pour ne pas perdre la meilleure solution connue avant mutation
					if (bestSolution.getPerformance() < enfants[i].getPerformance())
					{
						bestSolution = enfants[i];
					}
					mutation(&(enfants[i]));
					evaluer(&(enfants[i]), instance);
				}
			}
			//cout << "FIN CREATION ENFANTS" << endl;
			//REMPLACEMENT
			//cout << "DEBUT REMPLACEMENT" << endl;
			population = remplacementRang(population, enfants);
			//cout << "FIN REMPLACEMENT" << endl;

			population = trierPopulation(population);
			if (bestSolution.getPerformance() < population[population.size() - 1].getPerformance())
			{
				bestSolution = population[population.size() - 1];
			}
			/*
			cout << "#########################################" << endl;
			cout << "#########################################" << endl;
			bestSolution.afficherSolution(false);
			cout << "bestPerf: " << bestSolution.getPerformance() << endl;
			cout << "Nombre d'evaluations: " << compteurEvaluation << endl;
			cout << "#########################################" << endl;
			cout << "#########################################" << endl;
			*/
			if (compteurEvaluation > nombreEvaluationMax)
			{
				stop = true;
			}
		}
		cout << "#########################################" << endl;
		cout << "Meilleure Performance de la repetition: " << bestSolution.getPerformance() << endl;
		cout << "#########################################\n" << endl;
		performanceMoyenneFinale += (double)bestSolution.getPerformance() /(double)nombreRepetitions;
		Algo::extractSolutionToFile("AlgoGenetique", repetition, bestSolution, instance);
	}
}

vector<Solution> AlgoAG::generateRandomPopulation(int taillePopulation, int nombreVariables)
{
	vector<Solution> population(taillePopulation);
	for (size_t i = 0; i < population.size(); i++)
	{
		population[i] = generateRandomSolution(nombreVariables);
	}
	return population;
}

void AlgoAG::evaluerPopulation(vector<Solution>* population, Instance instance)
{
	for (size_t i=0; i< (*(population)).size(); i++)
	{
		evaluer(&((*(population))[i]),instance);
	}
}

bool compare(Solution i, Solution j)
{
	return i.getPerformance() < j.getPerformance();
}

Solution AlgoAG::getBestSolutionInPopulation(vector<Solution> population)
{
	vector<Solution> maPop(population);
	sort(maPop.begin(), maPop.end(), compare);
	return maPop[maPop.size()-1];
}

long int AlgoAG::getSommePerformances(vector<Solution> population)
{
	long int somme = 0;
	for (size_t i = 0; i< population.size(); i++)
	{
		somme += population[i].getPerformance();
	}
	return somme;
}

Solution AlgoAG::selectionParent(vector<Solution> population)
{
	//Etablissons les probabilité cumulées dêtre selectionné
	vector<double> probaCumulees(population.size());
	double somme = getSommePerformances(population);
	probaCumulees[0] = ((double)population[0].getPerformance()) / (double)somme;
	for (size_t i = 1; i< probaCumulees.size(); i++)
	{
		probaCumulees[i] = probaCumulees[i - 1] + ((double)population[i].getPerformance()) / (double)somme;
	}

	//On tire un double aléatoire entre 0 et 1
	double random = (double)rand() / (double)RAND_MAX;

	//Position of the literal to change
	int pos = 0;
	while (random > probaCumulees[pos])
	{
		pos++;
	}

	return population[pos];
}
//Populatiion triée en paramètre!!
Solution AlgoAG::selectionParentRang(vector<Solution> population)
{
	//Etablissons les probabilité cumulées dêtre selectionné
	vector<int> rangCumulees(population.size());
	rangCumulees[0] = 1;
	for (size_t i = 1; i< rangCumulees.size(); i++)
	{
		rangCumulees[i] = rangCumulees[i - 1] + i + 1;
	}

	//On tire int aléatoire entre 0 et dernier rang
	int random =rand() % (rangCumulees[rangCumulees.size() - 1]);

	//Position of the literal to change
	int pos = 0;
	while (random > rangCumulees[pos])
	{
		pos++;
	}

	return population[pos];
}

Solution AlgoAG::reproductionBinaire(Solution parent1, Solution parent2)
{
	Solution enfant(parent1.getLiterals().size());
	parent1.trierLiteralsParNumVar();
	parent2.trierLiteralsParNumVar();
	//On garde les literaux de même valeurs entre les parents
	for (size_t i=0; i<enfant.getLiterals().size(); i++)
	{
		if (parent1.getLiterals()[i].value == parent1.getLiterals()[i].value)
		{
			Literal litteral = parent1.getLiterals()[i];
			litteral.poidsEngendre = 0;
			enfant.setLiteral(i, litteral);
		}
		//On prend un des deux au hasard pour de la diversité
		else
		{
			int random = rand() % 2;
			if (random==0)
			{
				Literal litteral = parent1.getLiterals()[i];
				litteral.poidsEngendre = 0;
				enfant.setLiteral(i, litteral);
			}
			else if (random==1)
			{
				Literal litteral = parent2.getLiterals()[i];
				litteral.poidsEngendre = 0;
				enfant.setLiteral(i, litteral);
			}
		}
	}
	return enfant;
}

//Croisement uniforme
Solution AlgoAG::reproduction(Solution parent1, Solution parent2)
{
	Solution enfant(parent1.getLiterals().size());
	parent1.trierLiteralsParNumVar();
	parent2.trierLiteralsParNumVar();
	//On génère un masque
	vector<bool> masque(parent1.getLiterals().size());
	for (size_t i = 0; i<masque.size(); i++)
	{
		int random = rand() % 2;
		if (random == 1)
		{
			masque[i] = true;
		}
		else
		{
			masque[i] = false;
		}
	}

	//On echange les litteraux où le masque est à true
	for (size_t i = 0; i<enfant.getLiterals().size(); i++)
	{
		if (masque[i])
		{
			enfant.setLiteral(i, parent2.getLiterals()[i]);
		}
		else
		{
			enfant.setLiteral(i, parent1.getLiterals()[i]);
		}
	}
	return enfant;
}

void AlgoAG::mutation(Solution* solution)
{
	int nombreLitteraux = (*solution).getLiterals().size();
	int pos = rand() % nombreLitteraux;
	
	//On change le litteral concerné
	Literal litteral = (*solution).getLiterals()[pos];
	litteral.value = !litteral.value;
	(*solution).setLiteral(pos, litteral);
}

vector<Solution> AlgoAG::remplacement(vector<Solution> parents, vector<Solution> enfants)
{
	//Fusionnons les 2 populations
	vector<Solution> temporaire;
	temporaire.resize(parents.size() + enfants.size());
	for (size_t i=0; i< parents.size(); i++)
	{
		temporaire[i] = parents[i];
	}
	for (size_t i = 0; i< enfants.size(); i++)
	{
		temporaire[i+parents.size()] = enfants[i];
	}

	vector<Solution> prochaineGeneration(parents.size());
	for (size_t i=0; i<prochaineGeneration.size(); i++)
	{
		//Etablissons les probabilité cumulées dêtre selectionné
		vector<double> probaCumulees(temporaire.size());
		double somme = getSommePerformances(temporaire);
		probaCumulees[0] = ((double)temporaire[0].getPerformance()) / (double)somme;
		for (size_t i = 1; i< probaCumulees.size(); i++)
		{
			probaCumulees[i] = probaCumulees[i - 1] + ((double)temporaire[i].getPerformance()) / (double)somme;
		}

		//On tire un double aléatoire entre 0 et 1
		double random = (double)rand() / (double)RAND_MAX;

		//Position of the literal to change
		int pos = 0;
		while (random > probaCumulees[pos])
		{
			pos++;
		}
		//Ajout à la prochaine génération
		prochaineGeneration[i] = temporaire[pos];
		//Suppression pour éviter  les doublons
		temporaire.erase(temporaire.begin()+pos);
	}
	return prochaineGeneration;
}

vector<Solution> AlgoAG::remplacementRang(vector<Solution> parents, vector<Solution> enfants)
{
	//Fusionnons les 2 populations
	vector<Solution> temporaire;
	temporaire.resize(parents.size() + enfants.size());
	for (size_t i = 0; i< parents.size(); i++)
	{
		temporaire[i] = parents[i];
	}
	for (size_t i = 0; i< enfants.size(); i++)
	{
		temporaire[i + parents.size()] = enfants[i];
	}

	temporaire = trierPopulation(temporaire);

	vector<Solution> prochaineGeneration(parents.size());
	for (size_t i = 0; i<prochaineGeneration.size(); i++)
	{
		//Etablissons les probabilité cumulées dêtre selectionné
		vector<int> rangCumulees(temporaire.size());
		rangCumulees[0] = 1;
		for (size_t i = 1; i< rangCumulees.size(); i++)
		{
			rangCumulees[i] = rangCumulees[i - 1] + i + 1;
		}

		//On tire int aléatoire entre 0 et somme rang
		int random = rand() % (rangCumulees[rangCumulees.size() - 1]);

		//Position of the literal to change
		int pos = 0;
		while (random > rangCumulees[pos])
		{
			pos++;
		}
		//Ajout à la prochaine génération
		prochaineGeneration[i] = temporaire[pos];
		//Suppression pour éviter  les doublons
		temporaire.erase(temporaire.begin() + pos);
	}
	return prochaineGeneration;
}

//Tri les parents d'une population de la pire à la meilleure performance (de la + petite à la + grande car maximisation)
vector<Solution> AlgoAG::trierPopulation(vector<Solution> population)
{
	vector<Solution> newPop(population);
	sort(newPop.begin(), newPop.end(), compare);
	return newPop;
}
