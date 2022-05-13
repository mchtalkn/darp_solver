#include "DarpSolverHAC.h"
#include "BruteSDARP.h"


DarpSolverHAC::DarpSolverHAC(const std::vector<task>& tasks_, const std::vector<int> agentNodeIds_, const Graph& g_):DarpSolverBF(tasks_,agentNodeIds_,g_),hac(g_,tasks_)
{
}

void DarpSolverHAC::makeAssignments()
{
	hac.calculate_clusters();
	vector<vector<task>> bestSplit = hac.get_cluster(agentNodeIds.size());
	for (int i = 0; i < agentNodeIds.size(); i++) {
		Node n(agentNodeIds[i], vector<edge>());
		BruteSDARP::Ptr p(new BruteSDARP(graph, bestSplit[i], n));
		planners.push_back(p);
	}
}

