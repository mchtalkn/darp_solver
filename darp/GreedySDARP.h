#pragma once
#include "RoutePlanner.h"
class GreedySDARP: public RoutePlanner
{
	// Inherited via RoutePlanner
public:
	GreedySDARP(const Graph& g, const std::vector<task>& tasks, const Node& agent);
	virtual void calculate_route() override;
	virtual route getRoute() override;
	virtual Ptr clone() const override;
private:
	Node current;
	Graph graph;
};
