#include "Helpers.h"
#include <set>
#include <set>
#include <algorithm>
#include <exception>
#include <iterator>
using namespace std;
struct size_missmatch : public std::exception
{

};
std::vector<task> readTasksFromFile(ifstream& f)
{
	std::vector<task> res;
	int n;
	f >> n;
	while (n--) 
	{
		int from, to;
		f >> from;
		f >> to;
		res.push_back(task(from, to));
	} 
	return res;
}
std::vector<int> readAgentNodesFromFile(std::ifstream& f)
{
	vector<int> res;
	int n,id;
	f >> n;

	while (n--)
	{
		f >> id;
		res.push_back(id);
	}
	return res;
}
std::vector<std::vector<std::pair<int, task>>> generateSplits(const std::vector<task>& tasks, size_t splitCount)
{
	const std::vector < std::pair<int, task>> assigned;
	vector<std::vector<std::pair<int, task>>> res;
	generateSplitsHelper(tasks, splitCount, assigned,res);
	int i = 0;
	/*
	* 	for (auto split : a) {
		cout << "split " << i << endl;
		i++;
		for (auto t : split) {
			cout << "task from " << t.second.pickupNode << " to " << t.second.deliverNode << " added to agent " << t.first <<endl;
		}
	}

			  */
	return res;
}
//std::vector<std::vector<std::pair<int, task>>> generateSplitsHelper(const std::vector<task>& notAssigned, int splitCount, const std::set < std::pair<int, task>>& assigned, std::vector<std::vector<std::pair<int, task>>>& allComputed)
void generateSplitsHelper(const std::vector<task>& notAssigned, size_t splitCount, const std::vector < std::pair<int, task>>& assigned, std::vector<std::vector<std::pair<int, task>>>& allComputed)
{
	if (notAssigned.empty()) {
		if (find(allComputed.begin(), allComputed.end(), assigned) != allComputed.end()) {
			int bp = 0;
		}
		allComputed.push_back(assigned);
		return ;
	}
	task t(notAssigned[0]);
	std::vector<task> notAssignedNew(notAssigned.begin()+1,notAssigned.end());
	for (int i = 0; i < splitCount; i++) {
		vector<pair<int, task>> assignedNew(assigned);
		assignedNew.push_back(pair<int, task>(i, t));
		generateSplitsHelper(notAssignedNew, splitCount, assignedNew,allComputed);
	}
	return ;
}