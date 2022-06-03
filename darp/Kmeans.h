#pragma once
#include "Graph.h"
#include <vector>
#include "RoutePlanner.h"
#include <functional>
#include <string>
class Kmeans
{
private:
	struct assigned_task {
		const int id;
		const Node from;
		const Node to;
		int assigned_cluster;
		assigned_task(const int id_, const Node& from_, const Node& to_, const int assigned_cluster_) : id(id_), from(from_), to(to_), assigned_cluster(assigned_cluster_) {};
	};
	struct center {
		float r1, r2, r3, r4;
	};
public:
	Kmeans(const Graph& g_, const std::vector<task>& tasks_, int N_,std::string entity_center_distance=entity_center_distances[0], std::string center_assignment=center_assignments[0], std::string center_initializer=center_initializers[0]);
	const static std::vector<std::string> entity_center_distances;
	const static std::vector < std::string> center_assignments;
	const static std::vector < std::string> center_initializers;
	std::function<float(const Kmeans&, const assigned_task entity1, const int cluster_id)> calculate_entity_center_distance;
	std::function<void( Kmeans&)> assign_centers;
	std::function<void(Kmeans&)> init_centers;
	float cecd_r4(const assigned_task entity1, const int cluster_id) const;
	void ac_r4();
	void ic_random();
	std::vector<std::vector<task>> get_cluster();
	void calculate_clusters();
private:
	
	int N;
	int ITERATION_LIMIT = 1000;
	Graph g; //TODO may be const reference 
	std::vector<assigned_task> tasks;
	std::vector<center> centers;
	bool is_calculated = false;

};
