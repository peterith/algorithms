#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

struct Point {
	int x;
	int y;
};

struct Pair {
	Point firstPoint;
	Point secondPoint;
};

Point createPoint(int x, int y);
Pair createPair(Point firstPoint, Point secondPoint);
Pair findClosestPair(vector<Point> sortedPointsByX, vector<Point> sortedPointsByY);
double calculateDistance(Pair pair);
Pair findClosestSplitPair(vector<Point> sortedPointsByX, vector<Point> sortedPointsByY, double minimumDistance);

Pair findClosestPair(vector<Point> sortedPointsByX, vector<Point> sortedPointsByY) {
	vector<Point> leftPointsSortedByX, rightPointsSortedByX, leftPointsSortedByY, rightPointsSortedByY;
	Point largestLeftPoint =  sortedPointsByX[(sortedPointsByX.size() / 2) - 1];
	
	for (int i = 0; i < sortedPointsByX.size(); i++) {
		if (i < sortedPointsByX.size() / 2) {
			leftPointsSortedByX.push_back(sortedPointsByX[i]);
		} else {
			rightPointsSortedByX.push_back(sortedPointsByX[i]);
		}
	}
	for (int i = 0; i < sortedPointsByY.size(); i++) {
		if (sortedPointsByY[i].x <= largestLeftPoint.x) {
			leftPointsSortedByY.push_back(sortedPointsByY[i]);
		} else {
			rightPointsSortedByY.push_back(sortedPointsByY[i]);
		}
	}
	if (sortedPointsByX.size() == 2) {
		return createPair(sortedPointsByX[0], sortedPointsByX[1]);
	} else {
		double minimumDistance;
		Pair closestPair;
		
		Pair closestLeftPair = findClosestPair(leftPointsSortedByX, leftPointsSortedByY);
		Pair closestRightPair = findClosestPair(rightPointsSortedByX, rightPointsSortedByY);
		double leftPairDistance = calculateDistance(closestLeftPair);
		double rightPairDistance = calculateDistance(closestRightPair);
		if (leftPairDistance > rightPairDistance) {
			minimumDistance = rightPairDistance;
			closestPair = closestRightPair;
		} else {
			minimumDistance = leftPairDistance;
			closestPair = closestLeftPair;
		}
		Pair closestSplitPair = findClosestSplitPair(sortedPointsByX, sortedPointsByY, minimumDistance);
		if (calculateDistance(closestSplitPair) < minimumDistance) {
			closestPair = closestSplitPair;
		}
		return closestPair;
	}
}

Point createPoint(int x, int y) {
	Point point = {x, y};
	return point;
}

Pair createPair(Point firstPoint, Point secondPoint) {
	Pair pair = {firstPoint, secondPoint};
	return pair;
}

double calculateDistance(Pair pair) {
	return pow(pair.firstPoint.x - pair.secondPoint.x, 2) + pow(pair.firstPoint.y - pair.secondPoint.y, 2);
}

Pair findClosestSplitPair(vector<Point> sortedPointsByX, vector<Point> sortedPointsByY, double minimumDistance) {
	Point largestLeftPoint =  sortedPointsByX[(sortedPointsByX.size() / 2) - 1];
	vector<Point> nearByPoints;
	Pair closestPair;
	double closestDistance = DBL_MAX;
	
	for (int i = 0; i < sortedPointsByY.size(); i++) {
		double lowerThresholdDistance = largestLeftPoint.x - minimumDistance;
		double upperThresholdDistance = largestLeftPoint.x + minimumDistance;
		
		if (sortedPointsByY[i].x >= lowerThresholdDistance && sortedPointsByY[i].x <= upperThresholdDistance) {
			nearByPoints.push_back(sortedPointsByY[i]);
		}
	}
	for (int i = 0; i < nearByPoints.size(); i++) {
		int maximumNearByPointsCount = 7;
		if (maximumNearByPointsCount >  nearByPoints.size() - i - 1) {
			maximumNearByPointsCount = nearByPoints.size() - i - 1;
		}
		for (int j = 1; j < maximumNearByPointsCount; j++) {
			Pair pair = {nearByPoints[i], nearByPoints[i + j]};
			double distance = calculateDistance(pair);
			
			if (distance < closestDistance) {
				closestPair = pair;
				closestDistance = distance;
			}
		}
	}
	return closestPair;
}

int main() {
	vector<Point> v;
	
	cout << "Closest 2D Pair" << endl << endl;
	cout << "Input: ";
	for (int i = 1; i <= 8; i++) {
		v.push_back(createPoint(i,i * i));
		cout << "<" << v[i - 1].x << "," << v[i - 1].y << "> ";
	}
	Pair closestPair = findClosestPair(v, v);
	cout << endl << endl << "Output: <" << closestPair.firstPoint.x << "," << closestPair.firstPoint.y << "> <" << closestPair.secondPoint.x << "," << closestPair.secondPoint.y << ">";
}
