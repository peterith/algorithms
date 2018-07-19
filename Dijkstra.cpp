#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct Node;
struct Edge;
struct Graph;

void calculateShortestPathFrom(Graph& graph, Node* startingNode);
Graph createGraph();
void createNodesUpToId(Graph& graph, int maxId);
void createDirectedEdgeWithLength(Node* firstNode, Node* secondNode, int length);

struct Node {
	int id;
	vector<Edge*> incidentEdges;
	bool isExplored = false;
	int shortestLength;
};

struct Edge {
	Node* firstNode;
	Node* secondNode;
	int length;
};

struct Graph {
	vector<Node*> nodes;
	vector<Edge*> edges;
	vector<Node*> visitedNodes;
};

void calculateShortestPathFrom(Graph& graph, Node* startingNode) {
	startingNode->isExplored = true;
	startingNode->shortestLength = 0;
	graph.visitedNodes.push_back(startingNode);
	bool hasNodesToVisit = true;
	
	while(hasNodesToVisit) {
		Node* nextNodeToVisit;
		int shortestLength = INT_MAX;
		hasNodesToVisit = false;
		for (int i = 0; i < graph.visitedNodes.size(); i++) {
			for (int j = 0; j < graph.visitedNodes[i]->incidentEdges.size(); j++) {
				Edge* currentEdge = graph.visitedNodes[i]->incidentEdges[j];
				Node* currentNeighbourNode = currentEdge->secondNode;
				if (!currentNeighbourNode->isExplored) {
					hasNodesToVisit = true;
					int potentialShortestLength = graph.visitedNodes[i]->shortestLength + currentEdge->length;
					if (potentialShortestLength < shortestLength) {
						shortestLength = potentialShortestLength;
						nextNodeToVisit = currentNeighbourNode;
					}
				}
			}
		}
		if (hasNodesToVisit) {
			nextNodeToVisit->isExplored = true;
			nextNodeToVisit->shortestLength = shortestLength;
			graph.visitedNodes.push_back(nextNodeToVisit);
		}
	}
}

Graph createGraph() {
	Graph graph;
	createNodesUpToId(graph, 6);
	createDirectedEdgeWithLength(graph.nodes[0], graph.nodes[1], 1);
	createDirectedEdgeWithLength(graph.nodes[0], graph.nodes[2], 2);
	createDirectedEdgeWithLength(graph.nodes[2], graph.nodes[1], 4);
	createDirectedEdgeWithLength(graph.nodes[1], graph.nodes[3], 6);
	createDirectedEdgeWithLength(graph.nodes[2], graph.nodes[4], 3);
	createDirectedEdgeWithLength(graph.nodes[3], graph.nodes[4], 1);
	createDirectedEdgeWithLength(graph.nodes[3], graph.nodes[5], 2);
	createDirectedEdgeWithLength(graph.nodes[4], graph.nodes[5], 1);
	return graph;
}

void createNodesUpToId(Graph& graph, int maxId) {
	for (int i = 0; i < maxId; i++) {
		Node* node = new Node();
		node->id = i + 1;
		graph.nodes.push_back(node);
	}
}

void createDirectedEdgeWithLength(Node* firstNode, Node* secondNode, int length) {
	Edge* edge = new Edge();
	edge->firstNode = firstNode;
	edge->secondNode = secondNode;
	edge->length = length;
	firstNode->incidentEdges.push_back(edge);
}

int main() {
	Graph graph = createGraph();
	
	cout << "Dijkstra's Algorithm" << endl;
	cout << endl << "Input:" << endl;
	for (int i = 0; i < graph.nodes.size(); i++) {
		cout << "Node id: " << graph.nodes[i]->id << "; Incident to node(s): ";
		for (int j = 0; j < graph.nodes[i]->incidentEdges.size(); j++) {
			cout << graph.nodes[i]->incidentEdges[j]->secondNode->id << " ";
		}
		cout << endl;
	}
	cout << endl << "Output:" << endl;
	calculateShortestPathFrom(graph, graph.nodes[0]);
	for (int i = 0; i < graph.nodes.size(); i++) {
		cout << "Node id: " << graph.nodes[i]->id << "; Shortest length from node id 1: " << graph.nodes[i]->shortestLength << endl;
	}
}
