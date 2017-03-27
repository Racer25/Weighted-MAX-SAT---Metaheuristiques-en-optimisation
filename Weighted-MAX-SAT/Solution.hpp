#ifndef DEF_H_SOLUTION
#define DEF_H_SOLUTION
#include <string>
#include <vector>
#include "Instance.hpp"

class Solution
{
	private:
		std::vector<int> valeurs;				//literaux
		long int performance; //A MAXIMISER
		std::vector<int> poidsEngendresParLiteraux;
	public:
		Solution();
		Solution(std::vector<int> val);
		std::vector<int> getValeurs();
		void setValeurs(std::vector<int> vals);
		void setValeur(int pos, int val);
		std::vector<int> getPoidsEngendresParLiteraux();
		long int getPerformance();
		void afficherSolution(bool avecPoids);
		long int evaluerSolution( Instance instance);
		void trierValeurs();       //Trier par valeurs absolues croissantes les littéraux
		void trierValeursParPoidsEngendre();       //Trier par poids engendrés les littéraux
};
#endif
