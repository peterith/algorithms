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
	std::vector<Node*> nodes;
	std::vector<int> maximumWeightedIndependentSetValues;
	
	Graph() {
		createWeightedNode(1, 3);
		createWeightedNode(2, 1);
		createWeightedNode(3, 4);
		createWeightedNode(4, 2);
		createWeightedNode(5, 3);
	}
	
	void findMaximumWeightedIndependentSet() {
		maximumWeightedIndependentSetValues.push_back(0);
		maximumWeightedIndependentSetValues.push_back(nodes[0]->weight);
		
		for (int i = 1; i < nodes.size(); i++) {
			if (maximumWeightedIndependentSetValues[i] > maximumWeightedIndependentSetValues[i - 1] + nodes[i]->weight) {
				maximumWeightedIndependentSetValues.push_back(maximumWeightedIndependentSetValues[i]);
			} else {
				maximumWeightedIndependentSetValues.push_back(maximumWeightedIndependentSetValues[i - 1] + nodes[i]->weight);
			}
		}
	}
	
	void createWeightedNode(int nodeId, int weight) {
			nodes.push_back(new Node(nodeId, weight));
	}
	
	void displayInputNodes() {
		std::cout << "Input:" << std::endl;
		for (int i = 0; i < nodes.size(); i++) {
			std::cout << "Node id: " << nodes[i]->id << "; Weight: " << nodes[i]->weight << std::endl;
		}
		std::cout << std::endl;
	}
	
	void displayOutputNodes() {
		std::cout << "Output:" << std::endl;
		std::cout << "Maximum Weighted Independent Set Value: " << maximumWeightedIndependentSetValues[maximumWeightedIndependentSetValues.size() - 1];
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
