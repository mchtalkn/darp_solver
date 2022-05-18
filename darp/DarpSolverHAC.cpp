#include "DarpSolverHAC.h"
#include "BruteSDARP.h"


DarpSolverHAC::DarpSolverHAC(const std::vector<task>& tasks_, const std::vector<int> agentNodeIds_, const Graph& g_):DarpSolverBF(tasks_,agentNodeIds_,g_),hac(g_,tasks_)
{
	for (int a : agentNodeIds) {
		task t(a,a);
		hac.add_task(t);
	}
}

void DarpSolverHAC::set_hac_properties(const string& clustering, const string& distance)
{
	if (clustering == "single") {
		hac.calculate_cluster_distance = &HAC::ccd_single;
	}
	else if (clustering == "complete") {
		hac.calculate_cluster_distance = &HAC::ccd_complete;
	}
	else if (clustering == "average") {
		hac.calculate_cluster_distance = &HAC::ccd_average;
	}
	else {
		cerr << " clustering" << clustering << " did not recognized " << endl;
		exit(-1);
	}
	if (distance == "min_sg") {
		hac.calculate_entity_distance = &HAC::ced_min_sg;
	}
	else if (distance == "max_sg") {
		hac.calculate_entity_distance = &HAC::ced_max_sg;
	}
	else if (distance == "middle") {
		hac.calculate_entity_distance = &HAC::ced_middle;
	}
	else {
		cerr << "distance calculation " << distance << " couldnt recognized" << endl;
		exit(-1);
	}
}

void DarpSolverHAC::makeAssignments()
{
	hac.calculate_clusters();
	vector<vector<task>> bestSplit = hac.get_cluster();
	for (const vector<task>& split :bestSplit ) {
		vector<task> s;
		int agent = -1;
		for (const task& t : split) {
			
			if (t.pickupNode == t.deliverNode) {
				agent = t.pickupNode;
			}
			else s.push_back(t);
		}
		BruteSDARP::Ptr p(new BruteSDARP(graph, s, graph.getNode(agent)));
		planners.push_back(p);
	}
}

