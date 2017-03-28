#ifndef __ENTETE_H_
#define __ENTETE_H_
#include <vector>
#include "Instance.hpp"

using namespace std;
bool sat_header_read(string sat_file_name, int *nombreVariables, int *nombreClauses);
bool sat_data_read(string sat_file_name, vector< vector<int> > *valeursParClause, vector<int> *poids, int nombreVariables, int nombreClauses);
vector<Instance> recupererInstances();

#endif