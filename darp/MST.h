#pragma once
// NOT completed probably will be discarded
#include <vector>
#include "RoutePlanner.h"
#include <functional>
#include <string>
#include <unordered_set>
class MST
{
public:
	MST(const Graph& g_, const std::vector<task>& tasks_, const std::vector<int> agent_node_ids);
	void generate_mst();
	std::vector<std::vector<task>> get_split(int count, bool consider_agents = false);
protected:
	bool mst_generated = false;
	Graph g;
	Graph task_graph;
	Graph mst;
	std::vector<task> tasks;
	std::unordered_set<int> task_nodes;
	std::unordered_set<int> agent_tasks;
	bool check_subtree_agent(const Node& n, const edge& e);
	bool path_exists(int from, int to,int parent);
};
