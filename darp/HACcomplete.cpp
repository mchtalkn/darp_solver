#include "HACcomplete.h"
#include <math.h>
using namespace std;
HACcomplete::HACcomplete(const Graph& g_, const std::vector<task> tasks_):HAC(g_,tasks_)
{
}
float HACcomplete::calculate_distance(const std::vector<task>& cluster1, const std::vector<task> cluster2)
{
	float max_cost = -1;
	for (const task& t : cluster1) {
		for (const task& t2 : cluster2) {
			max_cost = max(max_cost, min(g.getEdgeCost(t.deliverNode, t2.pickupNode), g.getEdgeCost(t2.deliverNode, t.pickupNode)));
		}
	}
	return max_cost;
}
