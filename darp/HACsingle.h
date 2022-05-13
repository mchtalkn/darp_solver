#pragma once
#include "HAC.h"
class HACsingle: public HAC
{
	// Inherited via HAC
public:
	HACsingle(const Graph& g_, const std::vector<task> tasks_);
	virtual float calculate_distance(const std::vector<task>& cluster1, const std::vector<task> cluster2) override;
};
