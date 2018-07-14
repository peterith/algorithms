#include <iostream>
#include <vector>

using namespace std;

int randomSelect(vector<int>& inputVector, int leftLimit, int rightLimit, int orderStatistic);
int choosePivotPosition(int leftLimit);
int partitionAroundPivot(vector<int>& inputVector, int pivotPosition, int leftLimit, int rightLimit);
void swapPosition(vector<int>& inputVector, int firstPosition, int secondPosition);

int randomSelect(vector<int>& inputVector, int leftLimit, int rightLimit, int orderStatistic) {
	if (rightLimit - leftLimit <= 1) {
		return inputVector[orderStatistic];
	}
	int pivotPosition = choosePivotPosition(leftLimit);
	int newPivotPosition = partitionAroundPivot(inputVector, pivotPosition, leftLimit, rightLimit);
	if (newPivotPosition == orderStatistic) {
		return inputVector[orderStatistic];
	} else if (newPivotPosition < orderStatistic) {
		randomSelect(inputVector, newPivotPosition + 1, rightLimit, orderStatistic);
	} else {
		randomSelect(inputVector, leftLimit, newPivotPosition - 1, orderStatistic);
	}
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
		} else if (inputVector[i] < pivot) {
			swapPosition(inputVector, i, partitionBoundary);
			partitionBoundary++;
		}
	}
	swapPosition(inputVector, pivotPosition, partitionBoundary - 1);
	return partitionBoundary - 1;
}

void swapPosition(vector<int>& inputVector, int firstPosition, int secondPosition) {
	int temp = inputVector[firstPosition];
	inputVector[firstPosition] = inputVector[secondPosition];
	inputVector[secondPosition] = temp;
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
	int thirdOrderStatistic = randomSelect(inputVector, 0, inputVector.size() - 1, 2);
	cout << "Output: ";
	for (int i = 0; i < 10; i++) {
		cout << inputVector[i] << " ";
	}
	cout << endl << "3rd order statistic is: " << thirdOrderStatistic;
}
