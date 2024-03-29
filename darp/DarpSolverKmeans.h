#pragma once
#include "DarpSolverBF.h"
#include "Kmeans.h"
#include <vector>
class DarpSolverKmeans: public DarpSolverBF
{
public:
	typedef std::shared_ptr<DarpSolverKmeans> Ptr;
	DarpSolverKmeans(const std::vector<task>& tasks_, const std::vector<int>& agentNoddeIds_, const Graph& g_,const std::string& entity_center_distance = Kmeans::entity_center_distances[0], 
		const std::string& center_assignment = Kmeans::center_assignments[0], const std::string& center_initializer = Kmeans::center_initializers[0], const std::string route_planner = RoutePlanner::route_planners[0]);
	virtual void makeAssignments() override;
	void set_kmeans_properties(std::string entity_center_distance = Kmeans::entity_center_distances[0], std::string center_assignment = Kmeans::center_assignments[0], std::string center_initializer = Kmeans::center_initializers[0]);
private:
	int N = 0;
	Kmeans kmeans;
	string route_planner;
};

