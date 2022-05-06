#include <iostream>
#include "DarpSolverBF.h"
#include <math.h>
#include <fstream>
#include <Helpers.h>
using namespace std;
int main() {
	string graph_path = "graph.inp";
	
	ifstream f;
	f.open(graph_path);
	Graph g(f);
	vector<task> tasks = readTasksFromFile(f);
	vector<int> agentNodeIds = readAgentNodesFromFile(f);

	DarpSolverBF dsbf(tasks,agentNodeIds,g);
	dsbf.solve();
	auto r = dsbf.getRoutes();
	int bp = 0;
}