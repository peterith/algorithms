#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node;
struct Edge;
struct Graph;

void breadthFirstSearch(Graph& graph, Node* startingNode);

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

void breadthFirstSearch(Graph& graph, Node* startingNode) {
	queue<Node*> nodesToVisit;
	
	startingNode->isExplored = true;
	nodesToVisit.push(startingNode);
	while(nodesToVisit.size() != 0) {
		Node* node = nodesToVisit.front();
		cout << "Visiting node: " << node->id << endl;
		nodesToVisit.pop();
		for (int i = 0; i < node->incidentEdges.size(); i++) {
			Node* neighbourNode = node->incidentEdges[i]->secondNode;
			if (!neighbourNode->isExplored) {
				neighbourNode->isExplored = true;
				nodesToVisit.push(neighbourNode);
			}
		}
	}
}

int main() {
	Graph graph;
	
	for (int i = 0; i < 5; i++) {
		Node* node = new Node();
		node->id = i + 1;
		graph.nodes.push_back(node);
		//graph.nodes[i]->id = i + 1;
	}
	
	for (int i = 0; i < 4; i++) {
		Edge* edge = new Edge();
		edge->firstNode = graph.nodes[i];
		edge->secondNode = graph.nodes[i + 1];
		graph.nodes[i]->incidentEdges.push_back(edge);
	}
	
	Edge* edge = new Edge();
	edge->firstNode = graph.nodes[0];
	edge->secondNode = graph.nodes[4];
	graph.nodes[0]->incidentEdges.push_back(edge);
	
	cout << "Breath First Search" << endl << endl;
	cout << "Input:" << endl;
	for (int i = 0; i < graph.nodes.size(); i++) {
		cout << "Node id: " << graph.nodes[i]->id << ", Incident to Node(s): ";
		for (int j = 0; j < graph.nodes[i]->incidentEdges.size(); j++) {
			cout << graph.nodes[i]->incidentEdges[j]->secondNode->id << " ";
		}
		cout << endl;
	}
	cout << endl << "Output :" << endl;
	breadthFirstSearch(graph, graph.nodes[0]);
}