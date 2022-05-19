#include "GreedySDARP.h"
#include <vector>
using namespace std;
GreedySDARP::GreedySDARP(const Graph& g_, const std::vector<task>& tasks_, const Node& agent_):RoutePlanner(tasks_),graph(g_),current(agent_)
{
}

void GreedySDARP::calculate_route()
{
    vector<task> remaining(tasks);
   
    while (remaining.size() > 0)
    {
        float min_cost = INFINITY;
        int minid = -1;
        for (int i = 0; i < remaining.size(); i++) {
            float cost = graph.getEdgeCost(current.getId(), remaining[i].pickupNode);
            if (cost < min_cost) {
                minid = i;
                min_cost = cost;
            }
        }
        calculated_route.path.push_back(edge(current.getId(), remaining[minid].pickupNode, graph.getEdgeCost(current.getId(), remaining[minid].pickupNode)));
        calculated_route.path.push_back(edge(remaining[minid].pickupNode, remaining[minid].deliverNode, graph.getEdgeCost(remaining[minid].pickupNode, remaining[minid].deliverNode)));
        current = graph.getNode(remaining[minid].deliverNode);
        remaining.erase(remaining.begin()+minid);

    }
}

route GreedySDARP::getRoute()
{
    if (calculated_route.path.size() == 0) calculate_route();
    return calculated_route;

}

RoutePlanner::Ptr GreedySDARP::clone() const
{
    return Ptr(new GreedySDARP(*this));
}
