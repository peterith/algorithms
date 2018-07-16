#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node;
struct Edge;
struct Graph;

void topologicalSort(Graph& graph);
void depthFirstSearch(Graph& graph, Node* startingNode, int& currentLabel);

struct Node {
	int id;
	vector<Edge*> incidentEdges;
	bool isExplored = false;
	int topologicalOrder;
};

struct Edge {
	Node* firstNode;
	Node* secondNode;
};

struct Graph {
	vector<Node*> nodes;
	vector<Edge*> edges;
};

void topologicalSort(Graph& graph) {
	int currentLabel = graph.nodes.size();
	for (int i = 0; i < graph.nodes.size(); i++) {
		if (!graph.nodes[i]->isExplored) {
			depthFirstSearch(graph, graph.nodes[i], currentLabel);
		}
	}
}

void depthFirstSearch(Graph& graph, Node* startingNode, int& currentLabel) {
	for (int i = 0; i < startingNode->incidentEdges.size(); i++) {
		Node* neighbourNode = startingNode->incidentEdges[i]->secondNode;
		if (!neighbourNode->isExplored) {
			neighbourNode->isExplored = true;
			depthFirstSearch(graph, neighbourNode, currentLabel);
		}
	}
	startingNode->topologicalOrder = currentLabel;
	currentLabel--;
}

int main() {
	Graph graph;
	
	for (int i = 0; i < 5; i++) {
		Node* node = new Node();
		node->id = i + 1;
		graph.nodes.push_back(node);
		//graph.nodes[i]->id = i + 1;
	}
	
	for (int i = 0; i < 3; i++) {
		Edge* edge = new Edge();
		edge->firstNode = graph.nodes[i];
		edge->secondNode = graph.nodes[i + 1];
		graph.nodes[i]->incidentEdges.push_back(edge);
	}
	
	Edge* edge = new Edge();
	edge->firstNode = graph.nodes[0];
	edge->secondNode = graph.nodes[4];
	graph.nodes[0]->incidentEdges.push_back(edge);
	
	cout << "Topological Ordering" << endl << endl;
	cout << "Input:" << endl;
	for (int i = 0; i < graph.nodes.size(); i++) {
		cout << "Node id: " << graph.nodes[i]->id << ", Incident to Node(s): ";
		for (int j = 0; j < graph.nodes[i]->incidentEdges.size(); j++) {
			cout << graph.nodes[i]->incidentEdges[j]->secondNode->id << " ";
		}
		cout << endl;
	}
	cout << endl << "Output:" << endl;
	topologicalSort(graph);
	for (int i = 0; i < graph.nodes.size(); i++) {
		cout << "Node id: " << graph.nodes[i]->id << ", Topological order: " << graph.nodes[i]->topologicalOrder << endl;
	}
}
