#include <iostream>
#include <vector>

using namespace std;

vector<int> mergeSort(vector<int> inputVector);
vector<int> merge(vector<int> firstVector, vector<int> secondVector);

vector<int> mergeSort(vector<int> inputVector) {
	vector<int> firstVector, secondVector;
	
	if (inputVector.size() == 1) {
		return inputVector;
	} else {
		
		for (int i = 0; i < inputVector.size(); i++) {
			
			if (i < inputVector.size() / 2) {
				firstVector.push_back(inputVector[i]);
			} else {
				secondVector.push_back(inputVector[i]);
			}
		}
		
		return merge(mergeSort(firstVector), mergeSort(secondVector));
	}
}

vector<int> merge(vector<int> firstVector, vector<int> secondVector) {
	vector<int> outputVector;
	int j = 0, k = 0;
	
	for (int i = 0; i < firstVector.size() + secondVector.size(); i++) {
		
		if (j == firstVector.size()) {
			outputVector.push_back(secondVector[k]);
			k++;
		} else if (k == secondVector.size()) {
			outputVector.push_back(firstVector[j]);
			j++;
		} else if (firstVector[j] < secondVector[k]) {
			outputVector.push_back(firstVector[j]);
			j++;
		} else {
			outputVector.push_back(secondVector[k]);
			k++;
		}
	}
	
	return outputVector;
}

int main() {
	
	vector<int> inputVector;
	
	cout << "Merge Sort" << endl << endl;
	for (int i = 10; i > 0; i--) {
		inputVector.push_back(i);
	}
	
	cout << "Input: ";
	for (int i = 0; i < 10; i++) {
		cout << inputVector[i] << " ";
	}
	cout << endl << endl;
	
	vector<int> outputVector = mergeSort(inputVector);
	
		cout << "Output: ";
		for (int i = 0; i < outputVector.size(); i++) {
		cout << outputVector[i] << " ";
	}
}