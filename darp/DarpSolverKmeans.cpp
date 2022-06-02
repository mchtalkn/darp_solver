#include "DarpSolverKmeans.h"
#include "BruteSDARP.h"
#include "GreedySDARP.h"
using namespace std;


DarpSolverKmeans::DarpSolverKmeans(const std::vector<task>& tasks_, const std::vector<int>& agentNodeIds_, const Graph& g_, const std::string& entity_center_distance, const std::string& center_assignment, const std::string& center_initializer, const std::string route_planner_)
	: DarpSolverBF(tasks_, agentNodeIds_, g_), kmeans(g_, tasks_, agentNodeIds_.size(), entity_center_distance, center_assignment, center_initializer), N(agentNodeIds_.size()), route_planner(route_planner_)
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
		RoutePlanner::Ptr p;
		if (route_planner == "brute") {
			p = BruteSDARP::Ptr(new BruteSDARP(graph, clusters[min_id], graph.getNode(a)));
		}
		else if (route_planner == "greedy") {
			p = GreedySDARP::Ptr(new GreedySDARP(graph, clusters[min_id], graph.getNode(a)));
		}
		planners.push_back(p);

		planners.push_back(p);
		clusters.erase(clusters.begin() + min_id);
	}

}

void DarpSolverKmeans::set_kmeans_properties(std::string entity_center_distance, std::string center_assignment, std::string center_initializer)
{
}
