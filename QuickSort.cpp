#include <iostream>
#include <vector>

std::vector<int> inputVector;

void quickSort(int low, int high);
int selectPivot(int low);
int partitionAndReturnNewPivot(int pivot, int low, int high);
void swapPosition(int firstPosition, int secondPosition);

void quickSort(int low, int high) {
	while (low < high) {
		int pivot = selectPivot(low);
		int newPivot = partitionAndReturnNewPivot(pivot, low, high);
		if (newPivot - low < high - newPivot) {
			quickSort(low, newPivot - 1);
			low = newPivot + 1;
		} else {
			quickSort(newPivot + 1, high);
			high = newPivot - 1;
		}
	}
}

int selectPivot(int low) {
	return low;
}

int partitionAndReturnNewPivot(int pivot, int low, int high) {
	int partitionBoundary = low;
	for (int i = low; i <= high; i++) {
		if (i == pivot)
			partitionBoundary++;
		else if (inputVector[i] < inputVector[pivot]) {
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
	std::cout << "Quick Sort" << std::endl << std::endl;
}

void createVector() {
	for (int i = 10; i > 0; i--)
		inputVector.push_back(i);
}

void displayInput() {
	std::cout << "Input: ";
	for (int i = 0; i < inputVector.size(); i++)
		std::cout << inputVector[i] << " ";
	std::cout << std::endl << std::endl;
}

void displayOutput() {
	std::cout << "Output: ";
	for (int i = 0; i < inputVector.size(); i++)
		std::cout << inputVector[i] << " ";
}

int main() {
	displayTitle();
	createVector();
	displayInput();
	quickSort(0, inputVector.size() - 1);
	displayOutput();
}
