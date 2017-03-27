#ifndef DEF_H_INSTANCE
#define DEF_H_INSTANCE
#include <string>
#include <vector>

class Instance
{
	
	private:
		std::string nom;					//Nom du fichier de l'instance
		int nombreVariables;
		int nombreClauses;
		std::vector<int> poids;				//Poids de chaques clause
		std::vector< std::vector<int> > valeursParClause;	// Liste de litéraux de chaque clause
	public:
		Instance();
		Instance(std::string nm, int nV, int nC, std::vector<int> pds, std::vector< std::vector<int> > vPC);
		std::string getNom();
		int getNombreVariables();
		int getNombreClauses();
		std::vector<int> getPoids();
		std::vector< std::vector<int> > getValeursParClause();
		void afficherInstance();
};
#endif
