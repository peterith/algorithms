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
	std::queue<Node*> nodesToVisit;
	
	Graph() {
		createNodesUpToId(5);
		createDirectedEdge(0, 1);
		createDirectedEdge(1, 2);
		createDirectedEdge(0, 3);
		createDirectedEdge(3, 4);
	}
	
	void breadthFirstSearch(Node* startingNode) {
		startingNode->isExplored = true;
		nodesToVisit.push(startingNode);
		while(nodesToVisit.size() != 0) {
			Node* node = nodesToVisit.front();
			std::cout << "Visiting node: " << node->id << std::endl;
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
	
	void displayVisitedNodes() {
		std::cout << "Output:" << std::endl;
		breadthFirstSearch(nodes[0]);
	}
};

void displayTitle() {
	std::cout << "Breath First Search" << std::endl << std::endl;
}

int main() {
	Graph* graph = new Graph();
	graph->displayInputNodes();
	graph->displayVisitedNodes();
}
