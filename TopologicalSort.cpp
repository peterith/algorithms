#include <iostream>
#include <vector>
#include <queue>

struct Node;
struct Edge;
struct Graph;

struct Node {
	int id;
	std::vector<Edge*> incidentEdges;
	bool isExplored;
	int topologicalOrder;
	
	Node(int id) : id(id), isExplored(false) {}
};

struct Edge {
	Node* firstNode;
	Node* secondNode;
	
	Edge(Node* firstNode, Node* secondNode) : firstNode(firstNode), secondNode(secondNode) {}
};

struct Graph {
	std::vector<Node*> nodes;
	std::vector<Edge*> edges;
	
	Graph() {
		createNodesUpToId(5);
		createDirectedEdge(0, 1);
		createDirectedEdge(1, 2);
		createDirectedEdge(2, 3);
		createDirectedEdge(0, 4);
	}
	
	void topologicalSort() {
		int currentLabel = nodes.size();
		for (int i = 0; i < nodes.size(); i++) {
			if (!nodes[i]->isExplored)
				depthFirstSearch(nodes[i], currentLabel);
		}
	}
	
	void depthFirstSearch(Node* startingNode, int& currentLabel) {
		for (int i = 0; i < startingNode->incidentEdges.size(); i++) {
			Node* neighbourNode = startingNode->incidentEdges[i]->secondNode;
			if (!neighbourNode->isExplored) {
				neighbourNode->isExplored = true;
				depthFirstSearch(neighbourNode, currentLabel);
			}
		}
		startingNode->topologicalOrder = currentLabel;
		currentLabel--;
	}
	
	void createNodesUpToId(int maxId) {
		for (int i = 0; i < maxId; i++)
			nodes.push_back(new Node(i + 1));
	}

	void createDirectedEdge(int firstNodeId, int secondNodeId) {
		nodes[firstNodeId]->incidentEdges.push_back(new Edge(nodes[firstNodeId], nodes[secondNodeId]));
	}
	
	void displayInputNodes() {
		std::cout << "Input:" << std::endl;
		for (int i = 0; i < nodes.size(); i++) {
			std::cout << "Node id: " << nodes[i]->id << "; Adjacent node id(s): ";
			for (int j = 0; j < nodes[i]->incidentEdges.size(); j++)
				std::cout << nodes[i]->incidentEdges[j]->secondNode->id << " ";
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	
	void displayOutputNodes() {
		std::cout << "Output:" << std::endl;
		for (int i = 0; i < nodes.size(); i++)
			std::cout << "Node id: " << nodes[i]->id << "; Topological order: " << nodes[i]->topologicalOrder << std::endl;
	}
};

void displayTitle() {
	std::cout << "Topological Ordering" << std::endl << std::endl;
}

int main() {
	Graph* graph = new Graph();
	graph->displayInputNodes();
	graph->topologicalSort();
	graph->displayOutputNodes();
}
