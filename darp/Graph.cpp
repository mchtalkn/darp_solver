#include "Graph.h"
#include <algorithm>
#include <fstream>

using namespace std;
int Node::getId() const
{
    return id;
}

const std::vector<edge>& Node::getOutEdges() const
{
    return out_edges;
}

Node::Node(int id_, const std::vector<edge>& out_edges_,int x_, int y_): id(id_),out_edges(out_edges_),x(x_),y(y_)
{
}

void Node::addEdge(const edge& e)
{
    out_edges.push_back(e);
}

bool Node::operator==(const Node& rhs) const
{
    return rhs.id == id;
}

bool Node::doesExists() const
{
    return id != -1;
}


Graph::Graph(std::ifstream& f)
{
    int n;
    f >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        f >> x >> y;
        for (int j = 0; j < n; j++) {
            float cost;
            f >> cost;
            addEdge(edge(i, j, cost));
        }
    }
}

Graph::Graph(const std::vector<Node>& nodes, const std::vector<edge>& edges)
{
    this->nodes = nodes;
    this->edges = edges;
}

Graph::Graph(const std::vector<edge>& edges)
{
    for (const edge& e : edges) {

        this->addEdge(e);
    }
}

const Node& Graph::getNode(const int id) const
{
    Node dummy(id);
    auto p = find(nodes.begin(), nodes.end(), id);
    if (p == nodes.end()) throw NodeNotFound(id);
    else return *p;
}

const std::vector<Node>& Graph::getNodes() const
{
    return nodes;
}

const std::vector<edge>& Graph::getEdges() const
{
    return edges;
}

float Graph::getEdgeCost(const int from, const int to) const
{
    edge dummy(from, to, -1);
    auto p = find(edges.begin(), edges.end(), dummy);
    if (p == edges.end()) throw(EdgeNotFound(from, to)); // INFINITY might be returned
    else return (*p).cost;
}



void Graph::addEdge(const edge& e)
{
    edges.push_back(e);
    Node dummy(e.from);
    auto p = find(nodes.begin(), nodes.end(), dummy);
    if (p == nodes.end()) {
        dummy.addEdge(e);
        nodes.push_back(dummy);
    }
    else (*p).addEdge(e);
    dummy = Node(e.to);
    p = find(nodes.begin(), nodes.end(), dummy);
    if (p == nodes.end()) {
        nodes.push_back(dummy);
    }

}

void Graph::addNode(const Node& node)
{
    nodes.push_back(node);
    for (const edge& e : node.getOutEdges()) {
        if (find(edges.begin(), edges.end(), e) == edges.end()) addEdge(e);
    }
}

EdgeNotFound::EdgeNotFound(int from_, int to_):from(from_),to(to_)
{
}

NodeNotFound::NodeNotFound(int id_) :id(id_)
{
}

bool edge::operator==(const edge& e) const
{
    return e.from == from && e.to == to;
}
