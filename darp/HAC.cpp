#include "HAC.h"
#include <algorithm>
using namespace std;
const std::vector<std::string> HAC::entity_distances({"min_sg","max_sg","average_sg","middle"});
const std::vector<std::string> HAC::linkages({"single","complete","average"});
HAC::HAC(const Graph& g_, const std::vector<task> tasks_):g(g_),tasks(tasks_)
{
    
}

float HAC::ced_min_sg(const task t, const task t2) const
{
    return min(g.getEdgeCost(t.deliverNode, t2.pickupNode), g.getEdgeCost(t2.deliverNode, t.pickupNode));
}

float HAC::ced_max_sg(const task t, const task t2) const
{
    return max(g.getEdgeCost(t.deliverNode, t2.pickupNode), g.getEdgeCost(t2.deliverNode, t.pickupNode));
}

float HAC::ced_middle(const task t1, const task t2) const
{
    //TODO we do not have middle points as we do not have x,ys design might be revised
    Node t1p = g.getNode(t1.pickupNode);
    Node t1d = g.getNode(t1.deliverNode);
    Node t2p = g.getNode(t2.pickupNode);
    Node t2d = g.getNode(t2.deliverNode);
    float mx1, mx2, my1, my2;
    mx1 = (t1p.x + t1d.x) * 0.5;
    my1 = (t1p.y + t1d.y) * 0.5;
    mx2 = (t2p.x + t2d.x) * 0.5;
    my2 = (t2p.y + t2d.y) * 0.5;
    return sqrtf((mx1 - mx2) * (mx1 - mx2) + (my1 - my2) * (my1 - my2));
}

float HAC::ced_average(const task t, const task t2) const
{
    return (g.getEdgeCost(t.deliverNode, t2.pickupNode)+ g.getEdgeCost(t2.deliverNode, t.pickupNode))/2;
}

float HAC::ccd_single(const std::vector<task>& cluster1, const std::vector<task>& cluster2) const
{
    float min_cost = INFINITY;
    for (const task& t : cluster1) {
        for (const task& t2 : cluster2) {
            if (t.pickupNode == t.deliverNode && t2.pickupNode == t2.deliverNode) return INFINITY;
            min_cost = min(min_cost,calculate_entity_distance(*this,t,t2));
        }
    }
    return min_cost;
}

float HAC::ccd_complete(const std::vector<task>& cluster1, const std::vector<task> cluster2) const
{
    float max_cost = -1;
    for (const task& t : cluster1) {
        for (const task& t2 : cluster2) {
            if (t.pickupNode == t.deliverNode && t2.pickupNode == t2.deliverNode) return INFINITY;
            max_cost = max(max_cost,calculate_entity_distance(*this, t, t2));
        }
    }
    return max_cost;

}

float HAC::ccd_average(const std::vector<task>& cluster1, const std::vector<task> cluster2) const
{
    float total =0;
    int count = 0;
    for (const task& t : cluster1) {
        for (const task& t2 : cluster2) {
            if (t.pickupNode == t.deliverNode && t2.pickupNode == t2.deliverNode) return INFINITY;
            total += calculate_entity_distance(*this, t, t2);
            count++;
        }
    }
    return total / count;
}

void HAC::calculate_clusters()
{
    is_calculated = true;
    for (task_tree* t : forrest) {
        delete t;
    }
    forrest.clear();
    for (task& t : tasks) {
        task_tree* tp = new task_tree(t,g.getEdgeCost(t.pickupNode,t.deliverNode));
        forrest.push_back(tp);
    }
    
    while (forrest.size() > 1)
    {
        int mini = -1, minj = -1;
        float cost,mincost = INFINITY;
        for (int i = 0; i < forrest.size(); i++) {
            for (int j = i + 1; j < forrest.size(); j++) {
                cost = this->calculate_cluster_distance(*this, forrest[i]->get_leaves(), forrest[j]->get_leaves());
                if (cost < mincost) {
                    mini = i;
                    minj = j;
                    mincost = cost;
                }
            }
        }
        if (mincost == INFINITY) {
            int bp = 0;
            break;
        }
        task_tree* new_tree = new task_tree({forrest[mini],forrest[minj]}, forrest[mini]->distance + forrest[minj]->distance + mincost);
        forrest.erase(forrest.begin() + minj);
        forrest.erase(forrest.begin() + mini);
        forrest.push_back(new_tree);
    }
}

void HAC::add_task(const task& t)
{
    is_calculated = false;
    tasks.push_back(t);
}

std::vector<std::vector<task>> HAC::get_cluster() 
{
    vector<vector<task>> res;
    if (!is_calculated) calculate_clusters();
    for (const task_tree* const t:forrest) {
        res.push_back(t->get_leaves());
    }
    return res;
}
void get_cluster_helper(vector<vector<task>>& res ,const task_tree* t, const vector<task_tree*> parents)
{
    if (find(parents.begin(), parents.end(), t) == parents.end()) {
        res.push_back(t->get_leaves());
    }
    else
    {
        for (task_tree* t2 : t->children) get_cluster_helper(res, t2, parents);
    }
}

task_tree::task_tree()
{
}

task_tree::task_tree(const task& t_, float distance_):t(new task(t_)),distance(distance_)
{
}

task_tree::task_tree(const std::vector<task_tree*> children_,float distance_):children(children_),distance(distance_)
{
    
}

void task_tree::clear()
{
    if (t) delete t;
    for (auto child : children) child->clear();
}

std::vector<task> task_tree::get_leaves() const
{
    vector<task> leaves;
    if (t) leaves.push_back(*t);
    for (auto child : children) {
        vector<task> l = child->get_leaves();
        leaves.insert(leaves.end(), l.begin(), l.end());
    }
    return leaves;
}

