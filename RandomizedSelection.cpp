#include <iostream>
#include <vector>

std::vector<int> inputVector;

int randomSelect(int low, int high, int orderStatistic);
int selectPivot(int low);
int partitionAndReturnNewPivot(int pivot, int low, int high);
void swapPosition(int firstPosition, int secondPosition);

int randomSelect(int low, int high, int orderStatistic) {
	int pivot = selectPivot(low);
	int newPivot = partitionAndReturnNewPivot(pivot, low, high);
	if (newPivot == orderStatistic) {
		return inputVector[orderStatistic];
	} else if (newPivot < orderStatistic) {
		randomSelect(newPivot + 1, high, orderStatistic);
	} else {
		randomSelect(low, newPivot - 1, orderStatistic);
	}
}

int selectPivot(int low) {
	return low;
}

int partitionAndReturnNewPivot(int pivot, int low, int high) {
	int partitionBoundary = low;
	for (int i = low; i <= high; i++) {
		if (i == pivot) {
			partitionBoundary++;
		} else if (inputVector[i] < inputVector[pivot]) {
			swapPosition(i, partitionBoundary);
			partitionBoundary++;
		}
	}
	swapPosition(pivot, partitionBoundary - 1);
	return partitionBoundary - 1;
}

void swapPosition(int firstPosition, int secondPosition) {
	int temp = inputVector[firstPosition];
	inputVector[firstPosition] = inputVector[secondPosition];
	inputVector[secondPosition] = temp;
}

void displayTitle() {
	std::cout << "Randomized Selection" << std::endl << std::endl;
}

void createVector() {
	for (int i = 10; i > 0; i--) {
		inputVector.push_back(i);
	}
}

void displayInput() {
	std::cout << "Input: ";
	for (int i = 0; i < inputVector.size(); i++) {
		std::cout << inputVector[i] << " ";
	}
	std::cout << std::endl << std::endl;
}

void displayOutput(int thirdOrderStatistic) {
	std::cout << "Output: ";
	for (int i = 0; i < inputVector.size(); i++) {
		std::cout << inputVector[i] << " ";
	}
	std::cout << std::endl << "3rd order statistic: " << thirdOrderStatistic;
}

int main() {
	displayTitle();
	createVector();
	displayInput();
	int thirdOrderStatistic = randomSelect(0, inputVector.size() - 1, 2);
	displayOutput(thirdOrderStatistic);
}
