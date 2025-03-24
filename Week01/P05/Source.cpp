#include<iostream>
#include<vector>

using namespace std;

bool checkSortedWithRecursion(vector<int> v, int index) {
	// mỗi vòng index+=1 nên nếu index bằng được với chỉ số phần tử cao nhất thì điều kiện đúng 
	if (index == v.size() - 1) return true; 
	if (v[index] > v[index + 1]) return false; 
	return checkSortedWithRecursion(v, index + 1);
}


int main() {
	vector<int> v;
	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		int value; cin >> value;
		v.push_back(value);
	}
	int index = 0; // biến lưu vị trí để check 
	if (checkSortedWithRecursion(v, index)) {
		cout << "is Sorted" << endl;
	}
	else {
		cout << "not Sorted" << endl;
	}
	return 0;
}