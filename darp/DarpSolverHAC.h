#pragma once
#include "DarpSolverBF.h"
#include "HACsingle.h"
class DarpSolverHAC: public DarpSolverBF
{
	// Inherited via DarpSolver
public:
	DarpSolverHAC(const std::vector<task>& tasks, const std::vector<int> agentNodeIds, const Graph& g);

	typedef std::tr1::shared_ptr<DarpSolverHAC> Ptr;
	virtual void makeAssignments() override;
private:
	HACsingle hac;
};
