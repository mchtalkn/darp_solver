#include "MST.h"
#include <queue>
#include <map>
using namespace std;
MST::MST(const Graph& g_, const std::vector<task>& tasks_, const vector<int> agent_node_ids):g(g_),tasks(tasks_),task_graph(std::vector<edge>()), mst(std::vector<edge>())
{
	for (int i = 0; i < tasks.size(); i++) {
		for (int j = 0; j < tasks.size(); j++) {
			if (i == j) {
				task_graph.addEdge(edge(i,j,0));
			}
			else
			{
				task_graph.addEdge(edge(i, j, g.getEdgeCost(tasks[i].deliverNode, tasks[j].pickupNode)));
			}
		}
	}
	for (int i = 0; i < agent_node_ids.size();i++) {
		int a = agent_node_ids[i];
		int task_node_id = i + tasks.size();
		agent_tasks.insert(a);
		for (int j = 0; j < tasks.size(); j++) {
			task_graph.addEdge(edge(a, j, g.getEdgeCost(a, j)));
			task_graph.addEdge(edge(j, a, g.getEdgeCost(j, a)));
		}
	}
}

void MST::generate_mst()
{
	auto comp = [](edge rhs, edge lhs) {
		return rhs.cost > lhs.cost;
	};
	priority_queue<edge,vector<edge>,decltype(comp)> pq_edges(comp);
	const vector<edge>& all_edges = task_graph.getEdges();
	for (const edge& e : all_edges) {
		if (task_nodes.find(e.from) != task_nodes.end() && task_nodes.find(e.to) != task_nodes.end()) {
			pq_edges.push(e);
		}
	}
	while (pq_edges.size()>0)
	{
		edge e= pq_edges.top();
		if (path_exists(e.from, e.to, e.from));
	}
}

std::vector<std::vector<task>> MST::get_split(int count, bool consider_agents)
{
	return std::vector<std::vector<task>>();
}

bool MST::check_subtree_agent(const Node& n, const edge& e)
{
	return false;
}

bool MST::path_exists(int from, int to, int parent)
{

	auto& out_edges = mst.getNode(from).getOutEdges();
	for (const edge& e : out_edges) {
		if (e.to == parent) {
			continue;
		}
		if (e.to == to) return true;
		if (path_exists(e.to, to, from)) return true;
	}
	return false;
}
