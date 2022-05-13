#pragma once
#include "HAC.h"
class HACcomplete: public HAC
{
	// Inherited via HAC
	virtual float calculate_distance(const std::vector<task>& cluster1, const std::vector<task> cluster2) override;
};
