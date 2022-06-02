#pragma once
#include "DarpSolverBF.h"
#include "HAC.h"
class DarpSolverHAC: public DarpSolverBF
{
	// Inherited via DarpSolver
public:
	DarpSolverHAC(const std::vector<task>& tasks, const std::vector<int> agentNodeIds, const Graph& g);
	void set_hac_properties(const string& clustering, const string& distance, const string& route_planner = "brute");
	typedef std::tr1::shared_ptr<DarpSolverHAC> Ptr;
	virtual void makeAssignments() override;
private:
	HAC hac;
	string route_planner = "brute";
};
