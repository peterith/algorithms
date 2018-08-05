#include <iostream>
#include <vector>
#include <limits>

struct Node;
struct Edge;
struct Graph;

struct Node {
	int id;
	std::vector<Edge*> incidentEdges;
	bool isExplored;
	int shortestLength;
	
	Node(int id) : id(id), isExplored(false) {}
};

struct Edge {
	Node* firstNode;
	Node* secondNode;
	int length;
	
	Edge(Node* firstNode, Node* secondNode, int length) : firstNode(firstNode), secondNode(secondNode), length(length) {}
};

struct Graph {
	std::vector<Node*> allNodes;
	std::vector<Edge*> edges;
	std::vector<Node*> processedNodes;
	
	Graph() {
		createNodesUpToId(6);
		createDirectedEdge(0, 1, 1);
		createDirectedEdge(0, 2, 2);
		createDirectedEdge(2, 1, 4);
		createDirectedEdge(1, 3, 6);
		createDirectedEdge(2, 4, 3);
		createDirectedEdge(3, 4, 1);
		createDirectedEdge(3, 5, 2);
		createDirectedEdge(4, 5, 1);
	}
	
	void calculateShortestPathFrom(int startingNodeId) {
		updateNodeWithShortestLength(allNodes[startingNodeId], 0);
		while(processedNodes.size() != allNodes.size()) {
			Node* nodeToUpdate = NULL;
			int shortestLength = INT_MAX;
			searchForNodeWithShortestLength(nodeToUpdate, shortestLength);
			if (nodeToUpdate != NULL)
				updateNodeWithShortestLength(nodeToUpdate, shortestLength);
		}
	}
	
	void updateNodeWithShortestLength(Node* nodeToUpdate, int shortestLength) {
		nodeToUpdate->isExplored = true;
		nodeToUpdate->shortestLength = shortestLength;
		processedNodes.push_back(nodeToUpdate);
	}
	
	void searchForNodeWithShortestLength(Node*& nodeToUpdate, int& shortestLength) {
		for (int i = 0; i < processedNodes.size(); i++) {
			for (int j = 0; j < processedNodes[i]->incidentEdges.size(); j++) {
				Edge* currentEdge = processedNodes[i]->incidentEdges[j];
				if (!currentEdge->secondNode->isExplored) {
					int potentialShortestLength = processedNodes[i]->shortestLength + currentEdge->length;
					if (potentialShortestLength < shortestLength) {
						shortestLength = potentialShortestLength;
						nodeToUpdate = currentEdge->secondNode;
					}
				}
			}
		}
	}
	
	void createNodesUpToId(int maxNodeId) {
		for (int i = 0; i < maxNodeId; i++)
			allNodes.push_back(new Node(i + 1));
	}
	
	void createDirectedEdge(int firstNodeId, int secondNodeId, int length) {
		allNodes[firstNodeId]->incidentEdges.push_back(new Edge(allNodes[firstNodeId], allNodes[secondNodeId], length));
	}
	
	void displayInputNodes() {
		std::cout << "Input:" << std::endl;
		for (int i = 0; i < allNodes.size(); i++) {
			std::cout << "Node id: " << allNodes[i]->id << "; Adjacent (node id, edge length): ";
			for (int j = 0; j < allNodes[i]->incidentEdges.size(); j++)
				std::cout << "(" << allNodes[i]->incidentEdges[j]->secondNode->id << "," << allNodes[i]->incidentEdges[j]->length << ") ";
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	
	void displayOutputNodes() {
		std::cout << "Output:" << std::endl;
		for (int i = 0; i < allNodes.size(); i++)
			std::cout << "Node id: " << allNodes[i]->id << "; Shortest length from node id 1: " << allNodes[i]->shortestLength << std::endl;
	}
};

void displayTitle() {
	std::cout << "Dijkstra's Algorithm" << std::endl << std::endl;
}

int main() {
	Graph* graph = new Graph();
	displayTitle();
	graph->displayInputNodes();
	graph->calculateShortestPathFrom(0);
	graph->displayOutputNodes();
}
