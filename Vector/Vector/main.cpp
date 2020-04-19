#include "Vector.hpp"
#include <iostream>

#include<vector>
using namespace std;

int main()
{
	vector<int> a;
	Vector<int> arr2(3, 9);
	for (size_t i = 0; i < arr2.size(); ++i) {
		cout << arr2[i] << " ";
	}
	cout << endl;
	a.push_back(1);
	a.push_back(2);
	a.insert(a.begin() + 1, 8);
	Vector<int> arr;
	cout << arr.size() << " " << arr.capacity() << endl;
	arr.push_back(1);
	arr.push_back(2);
	arr.push_back(3);
	Vector<int> arr1(arr);
	for (size_t i = 0; i < arr.size(); ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
	for (size_t i = 0; i < arr.size(); ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
	arr.pop_back();
	for (size_t i = 0; i < arr.size(); ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
	arr.insert(arr.begin(), 9);
	for (size_t i = 0; i < arr.size(); ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
	arr.insert(arr.begin() + 1, 6);
	for (size_t i = 0; i < arr.size(); ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
	arr.erase(arr.begin());
	for (size_t i = 0; i < arr.size(); ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
	arr.erase(arr.begin(), arr.begin() + 2);
	for (size_t i = 0; i < arr.size(); ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}





