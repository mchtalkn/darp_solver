#include "BruteSDARP.h"

using namespace std;
BruteSDARP::BruteSDARP(const Graph& g,const vector<task>& t, const Node& agent):graph(g),RoutePlanner(t),current(agent)
{
}

void BruteSDARP::calculate_route()
{
	float minCost = INFINITY;
	calculated_route = getRouteRecursive(current, tasks);
}

route BruteSDARP::getRoute()
{
	if (calculated_route.path.size() == 0) calculate_route();
	return calculated_route;
}

RoutePlanner::Ptr BruteSDARP::clone() const
{
	return Ptr(new BruteSDARP(*this));
}

route BruteSDARP::getRouteRecursive(const Node& current, const std::vector<task>& remainingTasks)
{
	route r;
	if (remainingTasks.size() == 0) return r;
	r.cost = INFINITY;
	for (int i = 0; i < remainingTasks.size(); i++) {
		const task& t = remainingTasks[i];
		route tmp;
		vector<edge> e;
		float c1, c2;
		c1 = graph.getEdgeCost(current.getId(), t.pickupNode);
		c2 = graph.getEdgeCost(t.pickupNode, t.deliverNode);
		e.push_back(edge(current.getId(),t.pickupNode,c1));
		e.push_back(edge(t.pickupNode, t.deliverNode, c2));
		tmp.cost = c1 + c2;
		tmp.path = e;
		vector<task> tmpRemaining = remainingTasks;
		tmpRemaining.erase(tmpRemaining.begin() + i);
		tmp += getRouteRecursive(graph.getNode(t.deliverNode),tmpRemaining);
		if (tmp.cost < r.cost) r = tmp;
	}
	return r;
}

