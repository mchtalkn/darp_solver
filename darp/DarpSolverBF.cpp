#include "DarpSolverBF.h"
#include "Helpers.h"
#include "BruteSDARP.h"
DarpSolverBF::DarpSolverBF(const std::vector<task>& tasks, const std::vector<int> agentNodeIds, const Graph& g):DarpSolver(tasks,agentNodeIds),graph(g)
{
}

void DarpSolverBF::addSolver(RoutePlanner::Ptr p)
{
	planners.push_back(p);
}

void DarpSolverBF::solve()
{
	float bestCost = INFINITY;
	auto start = chrono::steady_clock::now();
	makeAssignments();
	auto end = chrono::steady_clock::now();
	assignment_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	start = chrono::steady_clock::now();

	for (auto& s : planners) s->calculate_route();
	end = chrono::steady_clock::now();
	solution_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

}

void DarpSolverBF::makeAssignments()
{
	float bestCost = INFINITY;
	vector<vector<task>> bestSplit;
	auto allSplits = generateSplits(tasks, agentNodeIds.size());
	for (auto split : allSplits) {
		float cost = 0;
		vector<BruteSDARP::Ptr> routers;
		vector<vector<task>> tasks(split.size());
		for (auto& t : split) {
			tasks[t.first].push_back(t.second);
		}
		for (int i = 0; i < agentNodeIds.size(); i++) {
			Node n=graph.getNode(agentNodeIds[i]);
			BruteSDARP router(graph, tasks[i],n);
			router.calculate_route();
			auto route = router.getRoute();
			cost += route.cost;
		}
		if (cost < bestCost) {
			bestSplit = tasks;
			bestCost = cost;
		}
	}
	for (int i = 0; i < agentNodeIds.size(); i++) {
		Node n = graph.getNode(agentNodeIds[i]);
		BruteSDARP::Ptr p(new BruteSDARP(graph, bestSplit[i],n));
		planners.push_back(p);
	}
}

DarpSolver::Ptr DarpSolverBF::copy()
{
	
	Ptr ptr (new DarpSolverBF(tasks,agentNodeIds,graph));
	for (auto& p : planners) {
		ptr->addSolver(p);
	}
	return ptr;
}
