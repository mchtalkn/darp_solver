#include "DarpSolver.h"
using namespace std;
DarpSolver::DarpSolver(const std::vector<task>& tasks_, const std::vector<int> agentNodeIds_): tasks(tasks_),agentNodeIds(agentNodeIds_)
{
}

DarpSolver::DarpSolver(const DarpSolver& ds)
{
    agentNodeIds = ds.agentNodeIds;
    for (auto p : ds.planners) {
        planners.push_back(p->clone());
    }
}

std::vector<route> DarpSolver::getRoutes()
{
    vector<route> routes;
    for (shared_ptr<RoutePlanner> rpp : planners) {
        RoutePlanner& rp = *rpp;
        routes.push_back(rp.getRoute());
    }
    return routes;
}

