#include<iostream>
#include<vector>

using namespace std;

int BinarySearch(vector<int> v, int left, int right) { // ta nạp vào 1 mảng đã được xoay, thì ta sẽ đi so sánh phần tử mid với phần tử right most, nếu mid vẫn nhỏ hơn thì phần từ nhỏ nhất vẫn nằm bên trái mid
	while (left < right) { // còn nếu mid lớn hơn thì tức là phần tử nhỏ nhất nằm bên phải mid 
		int mid = left+ (right- left) / 2;
		if (v[mid] < v[right]) {
			right = mid; // ta tìm kím phần bên trái của mảng, vì mid nhỏ hơn right nên vân có thể là nhỏ nhất nên ta vẫn giữ lại chứu không trừ 1 để skip phần tử 
		}
		else {
			left = mid+1; // tìm kiếm phần bên phải của mảng 
		}
	}
	return v[left]; 
}

int main() {
	vector<int> v;
	cout << "So luong phan tu: ";
	int n; cin >> n;
	cout << "Nhap mang: ";
	for (int i = 0; i < n; i++) {
		int value; cin >> value;
		v.push_back(value);
	}
	cout <<"Phan tu min trong mang: "<< BinarySearch(v, 0, n - 1);
	return 0;
}