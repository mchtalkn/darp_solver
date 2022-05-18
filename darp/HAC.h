#pragma once
#include "Graph.h"
#include "RoutePlanner.h"
#include <vector>
#include <memory>
#include <functional>
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
	std::function<float (const HAC&,const std::vector<task>& , const std::vector<task>)> calculate_cluster_distance;
	std::function<float(const HAC&,const task entity1, const task entity2)> calculate_entity_distance;
	float ced_min_sg(const task entity1, const task entity2) const;
	float ced_max_sg(const task entity1, const task entity2) const;
	float ced_middle(const task entity1, const task entity2) const;
	float ccd_single(const std::vector<task>& cluster1, const std::vector<task>& cluster2) const;
	float ccd_complete(const std::vector<task>& cluster1, const std::vector<task>cluster2) const;
	float ccd_average(const std::vector<task>& cluster1, const std::vector<task>cluster2) const;

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

