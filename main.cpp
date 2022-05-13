#include <iostream>
#include "DarpSolverBF.h"
#include "DarpSolverHAC.h"
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
	DarpSolverHAC dshc(tasks, agentNodeIds, g);
	dsbf.solve();
	dshc.solve();
	auto r1 = dsbf.getRoutes();
	auto r2 = dshc.getRoutes();
	int bp = 0;
}