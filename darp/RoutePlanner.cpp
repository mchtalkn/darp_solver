#include "RoutePlanner.h"
route route::operator+(const route& rhs) const
{
	route r;
	r.cost = cost + rhs.cost;
	r.path = path;
	r.path.insert(r.path.end(), rhs.path.begin(), rhs.path.end());
	return r;
}

route& route::operator+=(const route& rhs)
{
	*this = *this + rhs;
	return *this;
}

task::task(const int& pickupNode_, const int& deliverNode_):pickupNode(pickupNode_),deliverNode(deliverNode_)
{
}

int task::hash()
{
	return pickupNode*1234 + deliverNode;
}

RoutePlanner::RoutePlanner(const std::vector<task>& t): tasks(t)
{
}
