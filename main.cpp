#include <iostream>
#include "DarpSolverBF.h"
#include "DarpSolverHAC.h"
#include <math.h>
#include <fstream>
#include <Helpers.h>
#include "Kmeans.h"
#include "DarpSolverKmeans.h"
using namespace std;
int main() {
	string clustering[3] = {"single","complete","average"};
	string distances[3] = { "min_sg","max_sg","middle" };
	string graph_path = "graph.inp";
	
	ifstream f;
	f.open(graph_path);
	Graph g(f);
	vector<task> tasks = readTasksFromFile(f);
	vector<int> agentNodeIds = readAgentNodesFromFile(f);
	DarpSolverBF dsbf(tasks, agentNodeIds, g);
	dsbf.solve();
	auto r1 = dsbf.getRoutes();
	float total_cost = 0;
	float max_cost = 0;
	for (auto& r : r1) {
		total_cost += r.cost;
		max_cost = max(max_cost, r.cost);
	}
	printf(" brute force total cost %.0f max cost %.0f \n", total_cost, max_cost);
	for (const string& c : HAC::linkages) {
		for (const string& d : HAC::entity_distances) {
			total_cost = 0;
			max_cost = 0;
			DarpSolverHAC dshc(tasks, agentNodeIds, g);
			dshc.set_hac_properties(c,d);
			dshc.solve();
			r1 = dshc.getRoutes();
			for (auto& r : r1) {
				total_cost += r.cost;
				max_cost = max(max_cost, r.cost);
			}
			printf(" HAC %s %s total cost %.0f max cost %.0f \n", c.c_str(), d.c_str(), total_cost, max_cost);
		}
	}
	total_cost = 0;
	max_cost = 0;

	DarpSolverKmeans dskm(tasks,agentNodeIds,g);
	dskm.solve();
	for (auto& r : r1) {
		total_cost += r.cost;
		max_cost = max(max_cost, r.cost);
	}
	printf(" Kmeans total cost %.0f max cost %.0f \n", total_cost, max_cost);

	r1 = dskm.getRoutes();
	int bp = 0;
}