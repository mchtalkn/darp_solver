#pragma once
#include "Graph.h"
#include <memory>
struct task
{
	int pickupNode;
	int deliverNode;
	task(const int& pickupNode, const int& deliverNde);
	int hash();
	bool operator< (const task& t) const {
		return pickupNode < t.pickupNode || pickupNode == t.pickupNode && deliverNode < t.deliverNode;
	}
	bool operator == (const task& t) const {
		return pickupNode == t.pickupNode && deliverNode == t.deliverNode;
	}
};
struct route
{
	float cost = 0;
	std::vector<edge> path;
	route operator +(const route& rhs) const;
	route& operator +=(const route& rhs);
};
class RoutePlanner
{
public:
	typedef std::shared_ptr<RoutePlanner> Ptr;
	RoutePlanner(const std::vector<task>& t);
	virtual void calculate_route() = 0;
	virtual route getRoute() = 0;
	virtual Ptr clone() const = 0;
	const static std::vector < std::string> route_planners;
protected:
	route calculated_route;
	std::vector<task> tasks;
	
};
