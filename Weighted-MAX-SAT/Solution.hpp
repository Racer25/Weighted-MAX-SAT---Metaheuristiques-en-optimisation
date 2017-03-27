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
	public:
		Solution();
		Solution(std::vector<int> val);
		std::vector<int> getValeurs();
		long int getPerformance();
		void afficherSolution();
		long int evaluerSolution( Instance instance);
};
#endif
