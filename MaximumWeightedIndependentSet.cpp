#include <iostream>
#include <vector>
#include <limits>

struct Node;
struct Edge;
struct Graph;

struct Node {
	int id;
	int weight;
	
	Node(int id, int weight) : id(id), weight(weight) {}
};

struct Graph {
	std::vector<Node*> allNodes;
	std::vector<int> maximumWeightedIndependentSetValues;
	std::vector<Node*> nodesInOptimalSet;
	
	Graph() {
		createWeightedNode(1, 3);
		createWeightedNode(2, 1);
		createWeightedNode(3, 4);
		createWeightedNode(4, 2);
		createWeightedNode(5, 3);
	}
	
	void findMaximumWeightedIndependentSet() {
		getMaximumWeightedIndependentSetvalue();
		reconstructOptimalSet();
	}
	
	void getMaximumWeightedIndependentSetvalue() {
		maximumWeightedIndependentSetValues.push_back(0);
		maximumWeightedIndependentSetValues.push_back(allNodes[0]->weight);
		for (int i = 1; i < allNodes.size(); i++) {
			if (maximumWeightedIndependentSetValues[i] > maximumWeightedIndependentSetValues[i - 1] + allNodes[i]->weight) {
				maximumWeightedIndependentSetValues.push_back(maximumWeightedIndependentSetValues[i]);
			} else {
				maximumWeightedIndependentSetValues.push_back(maximumWeightedIndependentSetValues[i - 1] + allNodes[i]->weight);
			}
		}
	}
	
	void reconstructOptimalSet() {
		int i = 4;
		while (i > 0) {
			if (maximumWeightedIndependentSetValues[i] > maximumWeightedIndependentSetValues[i - 1] + allNodes[i]->weight) {
				i--;
			} else {
				nodesInOptimalSet.push_back(allNodes[i]);
				i = i - 2;
			}
		}
		if (i == 0) {
			nodesInOptimalSet.push_back(allNodes[0]);
		}
	}
	
	void createWeightedNode(int nodeId, int weight) {
		allNodes.push_back(new Node(nodeId, weight));
	}
	
	void displayInputNodes() {
		std::cout << "Input:" << std::endl;
		for (int i = 0; i < allNodes.size(); i++) {
			std::cout << "Node id: " << allNodes[i]->id << "; Weight: " << allNodes[i]->weight << std::endl;
		}
		std::cout << std::endl;
	}
	
	void displayOutputNodes() {
		std::cout << "Output:" << std::endl;
		std::cout << "Maximum weighted independent set value: " << maximumWeightedIndependentSetValues[maximumWeightedIndependentSetValues.size() - 1] << std::endl;
		std::cout << "Node id(s) in optimal set: ";
		for (int i = 0; i < nodesInOptimalSet.size(); i++) {
			std::cout << nodesInOptimalSet[i]->id << " ";
		}
	}
};

void displayTitle() {
	std::cout << "Maximum Weighted Independent Set" << std::endl << std::endl;
}

int main() {
	Graph* graph = new Graph();
	displayTitle();
	graph->displayInputNodes();
	graph->findMaximumWeightedIndependentSet();
	graph->displayOutputNodes();
}
