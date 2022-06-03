#pragma once
#include "DarpSolver.h"
using namespace std;
class DarpSolverBF: public DarpSolver
{

public:
	DarpSolverBF(const std::vector<task>& tasks, const std::vector<int> agentNodeIds,const Graph& g);

	void addSolver(RoutePlanner::Ptr);
	typedef std::shared_ptr<DarpSolverBF> Ptr;
	// Inherited via DarpSolver
	virtual void solve() override;

	virtual void makeAssignments() override;

	virtual DarpSolver::Ptr copy() override;
protected:
	Graph graph;
private:
	std::string route_planner = RoutePlanner::route_planners[0];
};
