#include "HACsingle.h"
#include <math.h>
using namespace std;
HACsingle::HACsingle(const Graph& g_, const std::vector<task> tasks_):HAC(g_,tasks_)
{
}
float HACsingle::calculate_distance(const std::vector<task>& cluster1, const std::vector<task> cluster2)
{
	float min_cost = INFINITY;
	for (const task& t : cluster1) {
		for (const task& t2 : cluster2) {
			min_cost = min(min_cost, min(g.getEdgeCost(t.deliverNode, t2.pickupNode),g.getEdgeCost(t2.deliverNode,t.pickupNode)));
		}
	}
	return min_cost;
}
