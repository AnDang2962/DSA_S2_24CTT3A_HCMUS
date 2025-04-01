#include<iostream>

using namespace std; 


bool ExistTwoNum(int arr[], int n, int target) { // cho mảng đã đuợc sắp xếp tăng dần
	int start = 0; // biến xét chỉ số bắt đầu của mảng 
	int sum = 0; // biến tính tổng 2 phần tử sẽ xét  
	int end = n - 1; // biến chỉ số cuối mảng 
	
	while (start < end) {
		sum += arr[start] + arr[end]; 
		if (sum == target) {
			return true;
		}
		//tại đây có 2 trường hợp là (sum> target) or ( sum< target) và mảng đã cho đax được săpx xếp
		else if (sum > target) {
			end--; // dời end về trước để giá trị nhỏ lại 
		}
		else {
			start++; // dời start đi tiếp để giá trị tăng lên 
		}
	}
	return false;
}
		 

int main() {
	cout << "Nhap so luong phan tu : ";
	int n; cin >> n;
	int* arr = new int[n];
	cout << "Nhap mang: ";
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	cout << "Nhap target: ";
	int target; cin >> target;
	if (ExistTwoNum(arr, n, target)) {
		cout << "YES" << endl;
	}
	else {
		cout << "NO" << endl;
	}

	return 0;
}