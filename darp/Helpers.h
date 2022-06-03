#pragma once
#include <vector>
#include <set>
#include "RoutePlanner.h"
#include <fstream>
std::vector<task> readTasksFromFile(std::istream& f);
std::vector<int> readAgentNodesFromFile(std::istream& f);
std::vector<std::vector<std::pair<int, task>>> generateSplits(const std::vector<task>& tasks, size_t splitCount);
void generateSplitsHelper(const std::vector<task>& notAssigned, size_t splitCount, const std::vector < std::pair<int, task>>& assigned, std::vector<std::vector<std::pair<int, task>>>& allComputed);
