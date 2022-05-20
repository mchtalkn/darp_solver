#include "DarpSolverKmeans.h"
#include "BruteSDARP.h"
using namespace std;
DarpSolverKmeans::DarpSolverKmeans( const std::vector<task>& tasks_, const std::vector<int>& agentNodeIds_, const Graph& g_, std::string entity_center_distance, std::string center_assignment, std::string center_initializer):DarpSolverBF(tasks_,agentNodeIds_,g_),kmeans(g_,tasks_,agentNodeIds_.size(),entity_center_distance,center_assignment,center_initializer),N(agentNodeIds_.size())
{
}

void DarpSolverKmeans::makeAssignments()
{
	vector<vector<task>> clusters =  kmeans.get_cluster();
	for (int a : agentNodeIds) {
		float min_cost = INFINITY;
		int min_id = -1;
		for (int i = 0; i < clusters.size(); i++) {
			float cost = INFINITY;
			for (const task& t : clusters[i]) {
				 cost = min(graph.getEdgeCost(a, t.pickupNode),cost);
			}
			if (cost < min_cost) {
				min_cost = cost;
				min_id = i;
			}

		}
		if (min_id == -1) {
			min_id = 0;
		}
		BruteSDARP::Ptr p(new BruteSDARP(graph, clusters[min_id], graph.getNode(a)));
		planners.push_back(p);
		clusters.erase(clusters.begin() + min_id);
	}

}

void DarpSolverKmeans::set_kmeans_properties(std::string entity_center_distance, std::string center_assignment, std::string center_initializer)
{
}
