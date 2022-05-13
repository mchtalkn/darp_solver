#pragma once
#include "HAC.h"
class HACcomplete: public HAC
{
public:
	HACcomplete(const Graph& g_, const std::vector<task> tasks_);
	// Inherited via HAC
	virtual float calculate_distance(const std::vector<task>& cluster1, const std::vector<task> cluster2) override;
};
