#include <iostream>
#include <vector>

using namespace std;

struct Node;
struct Edge;
struct Graph;

void depthFirstSearch(Graph& graph, Node* startingNode);
Graph createGraph();
void createNodesUpToId(Graph& graph, int maxId);
void createDirectedEdgeBetween(Node* firstNode, Node* secondNode);

struct Node {
	int id;
	vector<Edge*> incidentEdges;
	bool isExplored = false;
};

struct Edge {
	Node* firstNode;
	Node* secondNode;
};

struct Graph {
	vector<Node*> nodes;
	vector<Edge*> edges;
};

void depthFirstSearch(Graph& graph, Node* startingNode) {
	startingNode->isExplored = true;
	cout << "Visiting node: " << startingNode->id << endl;
	for (int i = 0; i < startingNode->incidentEdges.size(); i++) {
		Node* neighbourNode = startingNode->incidentEdges[i]->secondNode;
		if (!neighbourNode->isExplored) {
			depthFirstSearch(graph, neighbourNode);
		}
	}
}

Graph createGraph() {
	Graph graph;
	createNodesUpToId(graph, 5);
	createDirectedEdgeBetween(graph.nodes[0], graph.nodes[1]);
	createDirectedEdgeBetween(graph.nodes[1], graph.nodes[2]);
	createDirectedEdgeBetween(graph.nodes[0], graph.nodes[3]);
	createDirectedEdgeBetween(graph.nodes[3], graph.nodes[4]);
	return graph;
}

void createNodesUpToId(Graph& graph, int maxId) {
	for (int i = 0; i < maxId; i++) {
		Node* node = new Node();
		node->id = i + 1;
		graph.nodes.push_back(node);
	}
}

void createDirectedEdgeBetween(Node* firstNode, Node* secondNode) {
	Edge* edge = new Edge();
	edge->firstNode = firstNode;
	edge->secondNode = secondNode;
	firstNode->incidentEdges.push_back(edge);
}

int main() {
	Graph graph = createGraph();
	
	cout << "Depth First Search" << endl;
	cout << endl << "Input:" << endl;
	for (int i = 0; i < graph.nodes.size(); i++) {
		cout << "Node id: " << graph.nodes[i]->id << "; Incident to node(s): ";
		for (int j = 0; j < graph.nodes[i]->incidentEdges.size(); j++) {
			cout << graph.nodes[i]->incidentEdges[j]->secondNode->id << " ";
		}
		cout << endl;
	}
	cout << endl << "Output:" << endl;
	depthFirstSearch(graph, graph.nodes[0]);
}
