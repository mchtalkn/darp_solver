#pragma once
#include <vector>
#include <list>
#include <exception>
#include <string>
#include <iostream>
struct EdgeNotFound : public std::exception
{
	int from, to;
	EdgeNotFound(int from, int to);
	const char* what() const throw ()
	{
		std::string s;
		s = "Edge from " + std::to_string(from) + " to " + std::to_string(to) + " Not found";
		return s.c_str(); //TODO stack/heap problem here no need to solve
	}
};
struct NodeNotFound : public std::exception
{
	int id;
	NodeNotFound(int id);
	const char* what() const throw ()
	{
		std::string s;
		s = "Node  " + std::to_string(id) + "not found";
		return s.c_str(); //TODO stack/heap problem here no need to solve
	}
};
struct edge
{
	int from;
	int to;
	float cost;
	edge(int from_, int to_, float cost_) : from(from_), to(to_), cost(cost_) {};
	bool operator ==(const edge& e) const;
};
class Node
{
public:

	Node(int id_, const std::vector<edge>& out_edges_);
	void addEdge(const edge& e);
	int getId() const;
	const std::vector<edge>& getOutEdges() const;
	Node(int id_) :id(id_) {}
	bool operator ==(const Node& rhs) const;
	bool doesExists() const;
private:
	int id;
	std::vector<edge> out_edges;

};


class Graph
{
public:
	Graph(std::ifstream& f);
	Graph(const std::vector<Node>& nodes, const std::vector<edge>& edges);
	Graph(const std::vector<edge>& edges);
	const Node& getNode (const int id) const;
	const std::vector<Node>& getNodes() const;
	const std::vector<edge>& getEdges() const;
	float getEdgeCost(const int from, const int to) const;
	void addEdge(const edge& edge);
	void addNode(const Node& node);
private:
	std::vector<Node> nodes;
	std::vector<edge> edges;
	
};
