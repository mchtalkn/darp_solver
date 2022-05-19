#include "Kmeans.h"
#include <iostream>
#include <math.h>
using namespace std;
const std::vector<std::string> Kmeans::entity_center_distances = { "cecd_r4" };
const std::vector < std::string>Kmeans::center_assignments = { "ac_r4" };
const std::vector < std::string>Kmeans::center_initializers = { "random_medoid" };
Kmeans::Kmeans(const Graph& g_, const std::vector<task>& tasks_, int N_, std::string entity_center_distance, std::string center_assignment, std::string center_initializer):g(g_),N(N_)
{
	int i = 0;
	for (int i = 0; i < tasks_.size(); i++) {
		const task& t = tasks_[i];
		tasks.push_back(assigned_task(i, g.getNode(t.pickupNode), g.getNode(t.deliverNode), -1));
	}

	if (entity_center_distance == "cecd_r4") {
		calculate_entity_center_distance = &Kmeans::cecd_r4;
	}
	else {
		cerr << "entity_center_distance couldnt recognized" << endl;
		exit(-1);
	}
	if (center_assignment == "ac_r4") {
		assign_centers = &Kmeans::ac_r4;
	}
	else {
		cerr << "center_assignment couldnt recognized" << endl;
		exit(-1);

	}
	if (center_initializer == "random_medoid") {
		ic_random();
	}
	else {
		cerr << "center_initializer couldnt recognized" << endl;
		exit(-1);
	}
}

float Kmeans::cecd_r4(const assigned_task entity1, const int cluster_id) const
{
	const center& c = centers[cluster_id];
	
	return sqrt((entity1.from.x - c.r1) * (entity1.from.x - c.r1) + (entity1.from.y - c.r2) * (entity1.from.y - c.r2) + (entity1.to.x - c.r3) * (entity1.to.x - c.r3) + (entity1.to.x - c.r4) * (entity1.to.x - c.r4));
}

void Kmeans::ac_r4()
{
	vector<int> counts;
	centers.clear();
	for (int i = 0; i < N; i++) {
		centers.push_back(center());
		counts.push_back(0);
	}
	for (const assigned_task& ac : tasks) {
		int cid = ac.assigned_cluster;
		centers[cid].r1 += ac.from.x;
		centers[cid].r2 += ac.from.y;
		centers[cid].r3 += ac.to.x;
		centers[cid].r4 += ac.to.y;
		counts[cid]++;
	}
	for (int i = 0; i < centers.size(); i++) {
		centers[i].r1 /= counts[i];
		centers[i].r2 /= counts[i];
		centers[i].r3 /= counts[i];
		centers[i].r4 /= counts[i];
	}
}

void Kmeans::ic_random()
{
	is_calculated = false;
	vector<int> center_task_ids;
	while (centers.size() < N)
	{
		int tid = rand() % tasks.size();
		if (find(center_task_ids.begin(), center_task_ids.end(), tid) == center_task_ids.end()) {
			center c;
			c.r1 = tasks[tid].from.x;
			c.r2 = tasks[tid].from.y;
			c.r3 = tasks[tid].to.x;
			c.r4 = tasks[tid].to.y;
			centers.push_back(c);
		}
	}
	int bp = 0;
}

std::vector<std::vector<task>> Kmeans::get_cluster()
{
	std::vector<std::vector<task>> res(N);
	if (!is_calculated) calculate_clusters();
	for (const assigned_task& t : tasks) {
		res[t.assigned_cluster].push_back(task(t.from.getId(), t.to.getId()));
	}
	
	return res;
}

void Kmeans::calculate_clusters()
{
	is_calculated = true;
	int i = 0;
	bool same_assignment = false;
	while (!same_assignment && i++ < ITERATION_LIMIT)
	{
		same_assignment = true;
		for (assigned_task& at : tasks) {
			float min_cost = INFINITY;
			int min_cluster_id = -1;
			for (int cluster_id = 0; cluster_id < centers.size(); cluster_id++) {
				float cost = calculate_entity_center_distance(*this, at, cluster_id);
				if (cost < min_cost) {
					min_cost = cost;
					min_cluster_id = cluster_id;
				}
			}
			if (min_cluster_id == -1) {
				int bp = 0;
			}
			if (min_cluster_id != at.assigned_cluster) {
				at.assigned_cluster = min_cluster_id;
				same_assignment = false;
			}
		}
	}

}
