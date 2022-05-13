#include "HAC.h"
#include <algorithm>
using namespace std;
HAC::HAC(const Graph& g_, const std::vector<task> tasks_):g(g_),tasks(tasks_)
{
    
}

void HAC::calculate_clusters()
{
    is_calculated = true;
    vector<task_tree*> forrest;
    for (task& t : tasks) {
        task_tree* tp = new task_tree(t,g.getEdgeCost(t.pickupNode,t.deliverNode));
        forrest.push_back(tp);
        all_nodes.push_back(tp);
    }
    while (forrest.size() > 1)
    {
        int mini = -1, minj = -1;
        float cost,mincost = INFINITY;
        for (int i = 0; i < forrest.size(); i++) {
            for (int j = i + 1; j < forrest.size(); j++) {
                cost = calculate_distance(forrest[i]->get_leaves(), forrest[j]->get_leaves());
                if (cost < mincost) {
                    mini = i;
                    minj = j;
                    mincost = cost;
                }
            }
        }

        task_tree* new_tree = new task_tree({forrest[mini],forrest[minj]}, forrest[mini]->distance + forrest[minj]->distance + mincost);
        forrest.erase(forrest.begin() + minj);
        forrest.erase(forrest.begin() + mini);
        forrest.push_back(new_tree);
        all_nodes.push_back(new_tree);
    }
    tree = forrest[0];

    sort(all_nodes.begin(), all_nodes.end(), [](const task_tree* a, const task_tree* b) {
        return a->distance > b->distance;
        });
}

std::vector<std::vector<task>> HAC::get_cluster(int n)
{
    vector<task_tree*> parents;
    vector<vector<task>> res;
    if (!is_calculated) calculate_clusters();
    for (int i = 0; i < n -1; i++) {
        parents.push_back(all_nodes[i]);
    }
    get_cluster_helper(res,tree,parents);
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

