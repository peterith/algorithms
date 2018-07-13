#include <iostream>
#include <vector>

using namespace std;

void quickSort(vector<int>& inputVector, int leftLimit, int rightLimit);
int choosePivotPosition(int leftLimit);
int partitionAroundPivot(vector<int>& inputVector, int pivotPosition, int leftLimit, int rightLimit);


void quickSort(vector<int>& inputVector, int leftLimit, int rightLimit) {
	
	if (rightLimit - leftLimit <= 1) {
		return;
	}
	
	int pivotPosition = choosePivotPosition(leftLimit);
	int newPivotPosition = partitionAroundPivot(inputVector, pivotPosition, leftLimit, rightLimit);
	
	quickSort(inputVector, leftLimit, newPivotPosition - 1);
	quickSort(inputVector, newPivotPosition + 1, rightLimit);
}

int choosePivotPosition(int leftLimit) {
	return leftLimit;
}

int partitionAroundPivot(vector<int>& inputVector, int pivotPosition, int leftLimit, int rightLimit) {
	int pivot = inputVector[pivotPosition];
	int partitionBoundary = leftLimit;
	
	for (int i = leftLimit; i <= rightLimit; i++) {
		
		if (i == pivotPosition) {
			partitionBoundary++;
			continue;
		} else if (inputVector[i] < pivot) {
			int temp =  inputVector[i];
			inputVector[i] = inputVector[partitionBoundary];
			inputVector[partitionBoundary] = temp;
			partitionBoundary++;
		}
	}
	
	int temp = pivot;
	inputVector[pivotPosition] = inputVector[partitionBoundary - 1];
	inputVector[partitionBoundary - 1] = pivot;
	
	return partitionBoundary - 1;
}

int main() {
	vector<int> inputVector;
	
	cout << "Quick Sort" << endl << endl;
	for (int i = 10; i > 0; i--) {
		inputVector.push_back(i);
	}
	
	cout << "Input: ";
	for (int i = 0; i < 10; i++) {
		cout << inputVector[i] << " ";
	}
	cout << endl << endl;
	
	quickSort(inputVector, 0, inputVector.size() - 1);
	
	cout << "Output: ";
	for (int i = 0; i < 10; i++) {
		cout << inputVector[i] << " ";
	}
}
