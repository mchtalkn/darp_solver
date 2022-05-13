#pragma once
#include "Graph.h"
#include "RoutePlanner.h"
#include <vector>
#include <memory>

struct task_tree {
	task* t = nullptr;
	float distance = 0;
	std::vector<task_tree*> children;
	task_tree();
	task_tree(const task& t,float distance);
	task_tree(const std::vector<task_tree*> children,float distance);
	void clear();
	std::vector<task> get_leaves() const;
};
class HAC
{
public:
	HAC(const Graph& g_, const std::vector<task> tasks_);
	virtual float calculate_distance(const std::vector<task>& cluster1, const std::vector<task>cluster2) = 0;
	void calculate_clusters();
	std::vector<std::vector<task>> get_cluster(int n);
private:
protected:
	bool is_calculated = false;
	Graph g;
	std::vector<task> tasks;
	std::vector<task_tree*> all_nodes;
	task_tree* tree = nullptr;
	int cluster_count = 0;
};
void get_cluster_helper(std::vector<std::vector<task>>& res, const task_tree* t, const std::vector<task_tree*> parents);

