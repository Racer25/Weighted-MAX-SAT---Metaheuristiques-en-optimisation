#ifndef DEF_H_SOLUTION
#define DEF_H_SOLUTION
#include <string>
#include <vector>
#include "Instance.hpp"

struct Literal
{
	int numVar;
	bool value;
	int poidsEngendre;
};

class Solution
{
	private:
		std::vector<Literal> litteraux;				//literaux
		long int performance; //A MAXIMISER
	public:
		Solution();
		Solution(std::vector<Literal> litteraux);
		std::vector<Literal> getLiterals();
		void setLiterals(std::vector<Literal> litteraux);
		void setLiteral(int pos, Literal literal);
		long int getPerformance();
		void afficherSolution(bool avecPoids);
		long int evaluerSolution( Instance instance);
		void trierLiteralsParNumVar();       //Trier par numVar croissant
		void trierLiteralsParPoidsEngendre();       //Trier par poids engendrés les littéraux
		int getSommePoids();
};
#endif
