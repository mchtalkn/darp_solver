#pragma once
#include <vector>
#include "RoutePlanner.h"
#include <memory>

class DarpSolver
{
public:
	typedef std::shared_ptr<DarpSolver> Ptr;
	DarpSolver(const std::vector<task>&tasks, const std::vector<int> agentNodeIds);
	virtual void solve() = 0;
	virtual void makeAssignments() = 0;
	virtual std::vector<route> getRoutes();
	virtual Ptr copy() = 0;
	long long assignment_time = -1;
	long long solution_time = -1;
protected:
	DarpSolver(const DarpSolver& ds);
	std::vector<RoutePlanner::Ptr> planners;
	std::vector<int> agentNodeIds;
	std::vector<task> tasks;
	DarpSolver(DarpSolver&& ds) = default;

};
