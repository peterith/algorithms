#include <iostream>
#include <vector>
#include <queue>
#include <limits>

struct Node;
struct Edge;
struct Graph;
struct minHeap;

struct Node {
	int id;
	std::vector<Edge*> incidentEdges;
	bool isExplored;
	int shortestLength;
	
	Node(int id) : id(id), isExplored(false), shortestLength(INT_MAX) {}
};

struct Edge {
	Node* firstNode;
	Node* secondNode;
	int length;
	
	Edge(Node* firstNode, Node* secondNode, int length) : firstNode(firstNode), secondNode(secondNode), length(length) {}
};

struct minHeap {
	bool operator()(Node* firstNode, Node* secondNode) {
		return firstNode->shortestLength > secondNode->shortestLength;
	}
};

struct Graph {
	std::vector<Node*> nodes;
	std::vector<Edge*> edges;
	std::priority_queue<Node*, std::vector<Node*>, minHeap> minimumLengthHeap;
	
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
		nodes[startingNodeId]->shortestLength = 0;
		minimumLengthHeap.push(nodes[startingNodeId]);
		while (!minimumLengthHeap.empty()) {
			Node* nodeToProcess = minimumLengthHeap.top();
			minimumLengthHeap.pop();
			nodeToProcess->isExplored = true;
			for (int i = 0; i < nodeToProcess->incidentEdges.size(); i++) {
				Node* neighbourNode = nodeToProcess->incidentEdges[i]->secondNode;
				if (!neighbourNode->isExplored) {
					int length = nodeToProcess->shortestLength + nodeToProcess->incidentEdges[i]->length;
					if (length < neighbourNode->shortestLength) {
						neighbourNode->shortestLength = length;
						minimumLengthHeap.push(neighbourNode);
					}
				}
			}
		}
	}
	
	void createNodesUpToId(int maxNodeId) {
		for (int i = 0; i < maxNodeId; i++)
			nodes.push_back(new Node(i + 1));
	}
	
	void createDirectedEdge(int firstNodeId, int secondNodeId, int length) {
		nodes[firstNodeId]->incidentEdges.push_back(new Edge(nodes[firstNodeId], nodes[secondNodeId], length));
	}
	
	void displayInputNodes() {
		std::cout << "Input:" << std::endl;
		for (int i = 0; i < nodes.size(); i++) {
			std::cout << "Node id: " << nodes[i]->id << "; Adjacent (node id, edge length): ";
			for (int j = 0; j < nodes[i]->incidentEdges.size(); j++)
				std::cout << "(" << nodes[i]->incidentEdges[j]->secondNode->id << "," << nodes[i]->incidentEdges[j]->length << ") ";
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	
	void displayOutputNodes() {
		std::cout << "Output:" << std::endl;
		for (int i = 0; i < nodes.size(); i++)
			std::cout << "Node id: " << nodes[i]->id << "; Shortest length from node id 1: " << nodes[i]->shortestLength << std::endl;
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
