#include<iostream>
#include<vector>

using namespace std;

int LinearSearch(vector<int> v, int n, int k) {
	for (int i = 0; i < n; i++) {
		if (v[i] == k) {
			return i;
		}
	}
	return -1;
}

int main() {
	cout << "Nhap so luong phan tu cua mang: ";
	int n; cin >> n; // số lượng phần tử của mảng 
	cout << "Nhap target: ";
	int k; cin >> k; // Phần tử cần tìm 
	vector<int> v;
	cout << "Nhap mang: ";
	for (int i = 0; i < n; i++) {
		int value; cin >> value;
		v.push_back(value);
	}
	int res= LinearSearch(v, n, k);
	cout << "Vi tri target trong mang: ";
	cout << res << endl;
	return 0;
}