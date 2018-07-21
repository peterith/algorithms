#include <iostream>
#include <vector>
#include <limits>

struct Node;
struct Edge;
struct Graph;

struct Node {
	int id;
	std::vector<Edge*> incidentEdges;
	std::vector<Edge*> reverseIncidentEdges;
	bool isExplored;
	
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
	std::vector<Edge*> minimumSpanningEdges;
	
	Graph() {
		createNodesUpToId(6);
		createUndirectedEdge(0, 1, 1);
		createUndirectedEdge(0, 2, 2);
		createUndirectedEdge(2, 1, 4);
		createUndirectedEdge(1, 3, 6);
		createUndirectedEdge(2, 4, 3);
		createUndirectedEdge(3, 4, 1);
		createUndirectedEdge(3, 5, 2);
		createUndirectedEdge(4, 5, 1);
	}
	
	void findMinimumSpanningTree() {
		processNode(allNodes[0]);
		while(processedNodes.size() != allNodes.size()) {
			Edge* edgeToAdd = NULL;
			int shortestLength = INT_MAX;
			searchIncidentEdges(edgeToAdd, shortestLength);
			searchReverseIncidentEdges(edgeToAdd, shortestLength);
			processNode(edgeToAdd->secondNode);
			minimumSpanningEdges.push_back(edgeToAdd);
		}
	}
	
	void searchIncidentEdges(Edge*& edgeToAdd, int& shortestLength) {
		for (int i = 0; i < processedNodes.size(); i++) {
			for (int j = 0; j < processedNodes[i]->incidentEdges.size(); j++) {
				Edge* currentEdge = processedNodes[i]->incidentEdges[j];
				if (!currentEdge->secondNode->isExplored) {
					if (currentEdge->length < shortestLength) {
						shortestLength = currentEdge->length;
						edgeToAdd = currentEdge;
					}
				}
			}
		}
	}
	
	void searchReverseIncidentEdges(Edge*& edgeToAdd, int& shortestLength) {
		for (int i = 0; i < processedNodes.size(); i++) {
			for (int j = 0; j < processedNodes[i]->reverseIncidentEdges.size(); j++) {
				Edge* currentEdge = processedNodes[i]->reverseIncidentEdges[j];
				if (!currentEdge->secondNode->isExplored) {
					if (currentEdge->length < shortestLength) {
						shortestLength = currentEdge->length;
						edgeToAdd = currentEdge;
					}
				}
			}
		}
	}
	
	void processNode(Node* nodeToProcess) {
		nodeToProcess->isExplored = true;
		processedNodes.push_back(nodeToProcess);
	}
	
	void createNodesUpToId(int maxNodeId) {
		for (int i = 0; i < maxNodeId; i++) {
			allNodes.push_back(new Node(i + 1));
		}
	}
	
	void createUndirectedEdge(int firstNodeId, int secondNodeId, int length) {
		createDirectedEdge(firstNodeId, secondNodeId, length);
		allNodes[secondNodeId]->reverseIncidentEdges.push_back(new Edge(allNodes[secondNodeId], allNodes[firstNodeId], length));
	}
	
	void createDirectedEdge(int firstNodeId, int secondNodeId, int length) {
		allNodes[firstNodeId]->incidentEdges.push_back(new Edge(allNodes[firstNodeId], allNodes[secondNodeId], length));
	}
	
	void displayInputNodes() {
		std::cout << "Input:" << std::endl;
		for (int i = 0; i < allNodes.size(); i++) {
			std::cout << "Node id: " << allNodes[i]->id << "; Adjacent (node id, edge length): ";
			for (int j = 0; j < allNodes[i]->incidentEdges.size(); j++) {
				std::cout << "(" << allNodes[i]->incidentEdges[j]->secondNode->id << "," << allNodes[i]->incidentEdges[j]->length << ") ";
			}
			for (int j = 0; j < allNodes[i]->reverseIncidentEdges.size(); j++) {
				std::cout << "(" << allNodes[i]->reverseIncidentEdges[j]->secondNode->id << "," << allNodes[i]->reverseIncidentEdges[j]->length << ") ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	
	void displayOutputNodes() {
		std::cout << "Output:" << std::endl;
		std::cout << "Minimum Spanning Edges (first node id, second node id, edge length): ";
		for (int i = 0; i < minimumSpanningEdges.size(); i++) {
			std::cout << "(" << minimumSpanningEdges[i]->firstNode->id << "," << minimumSpanningEdges[i]->secondNode->id << ","<< minimumSpanningEdges[i]->length << ") ";
		}
		std::cout << std::endl;
	}
};

void displayTitle() {
	std::cout << "Prim's Algorithm" << std::endl << std::endl;
}

int main() {
	Graph* graph = new Graph();
	displayTitle();
	graph->displayInputNodes();
	graph->findMinimumSpanningTree();
	graph->displayOutputNodes();
}
