#include<iostream>
#include<vector>
using namespace std;

int LinearSearchSentinel(vector<int> v, int n, int k) {
	v.push_back(k);
	int i = 0;
	while (v[i] != k) {
		i++;
	}
	if (i < n) return i;
	if (i == n) return - 1;
}

int main() {
	vector<int> v;
	int n; 
	cout << "Nhap so luong phan tu: ";
	cin >> n;
	cout << "Nhap target: ";
	int k; cin >> k;
	cout << "Nhap mang: ";
	for (int i = 0; i < n; i++) {
		int value; cin >> value; 
		v.push_back(value);
	}
	cout <<"Vi tri cua target:"<< LinearSearchSentinel(v, n, k) << endl;
	return 0;
}

