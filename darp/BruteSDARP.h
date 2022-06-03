#pragma once
#include "RoutePlanner.h"
#include <chrono>

class BruteSDARP: public virtual RoutePlanner
{
public:
	BruteSDARP(const Graph& g,const std::vector<task>& tasks,const Node& agent);
	void calculate_route();
	route getRoute();
	Ptr clone() const;
private:
	Node current;
	Graph graph;
	
	route getRouteRecursive(const Node& current, const std::vector<task>& remainingTasks);

};
