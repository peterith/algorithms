#include <iostream>
#include <vector>

using namespace std;

vector<int> v;


vector<int> mergeSort(vector<int> v);
vector<int> merge(vector<int> a, vector<int> b);

vector<int> mergeSort(vector<int> v) {
	vector<int> a, b;
	
	if (v.size() == 1) {
		cout << "Returning single element --> " << v[0] << endl;
		return v;
	} else {
		
		cout << "Splitting elements --> ";
		for (int i = 0; i < v.size(); i++) {
			if (i < v.size() / 2) {
				a.push_back(v[i]);
				cout << a[i] << " ";
			} else {
				b.push_back(v[i]);
				cout << b[i - (v.size() / 2)] << " ";
			}
		}
		cout << endl;
		
		vector<int> a2 = mergeSort(a);
		vector<int> b2 = mergeSort(b);
		
		return merge(a2, b2);
	}
}

vector<int> merge(vector<int> a, vector<int> b) {
	vector<int> c;
	int j = 0, k = 0;
	
	cout << "Forming elements --> ";
	for (int i = 0; i < a.size() + b.size(); i++) {
		
		if (j == a.size()) {
			c.push_back(b[k]);
			k++;
		} else if (k == b.size()) {
			c.push_back(a[j]);
			j++;
		}
		else if (a[j] < b[k]) {
			c.push_back(a[j]);
			j++;
		} else {
			c.push_back(b[k]);
			k++;
		}
		cout << c[i] << " ";
	}
	cout << endl;
	
	return c;
}

int main() {
	
	cout << "Merge Sort Program" << endl << endl;
	for (int i = 10; i > 0; i--) {
		v.push_back(i);
	}
	
	cout << "Input: ";
	for (int i = 0; i < 10; i++) {
		cout << v[i] << " ";
	}
	cout << endl << endl;
	
	cout << "Tasks:" << endl;
	vector<int> answer = mergeSort(v);
	
		cout << endl << "Output:" << endl;
		for (int i = 0; i < v.size(); i++) {
		cout << answer[i] << " ";
	}
}