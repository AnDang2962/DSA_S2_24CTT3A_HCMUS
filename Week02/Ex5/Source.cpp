#include<iostream>
#include<vector>

using namespace std;
// Sử dụng 2 con trỏ để duyệt 
int  MinimalLengthSubarray(int arr[], int n, int target) {
	int sum = 0; // biến tính tổng các số mảng con
	int length = 0; // biến chứa độ dài mảng con
	int res = -1; // biến kết quả để return ;
	int start = 0; // chỉ số bắt đàua của mangr 
	for (int i = 0; i < n; i++) {
		sum += arr[i];
		length += 1;
		// vòng lặp để loại bỏ phần tử nếu mảng con lớn hơn target
		while (sum >= target) { // nếu mảng con cứ lớn hơn target thì ta tiếp tục bỏ 1 phần tử ở start ra 
			sum -= arr[start];
			res = length; // trước khi cập nhật độ dài thì ta cập nhật lại kết quả, vì nếu điều kiện sai thì vòng lặp dừng tức là length sẽ không đúng và length cũ sẽ là kết quả độ dài ta mong muốn
			length -= 1;
			start += 1;
		}
	}
	if (res == -1) {
		return 0;
	}
	else {
		return res;
	}
}

int main() {
	cout << "So luong phan tu cua mang: ";
	int n; cin >> n;
	int* arr = new int[n];
	cout << "Nhap mang: ";
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	cout << "Nhap target: ";
	int target; cin >> target;
	int res= MinimalLengthSubarray(arr, n, target);
	cout << "Do dai ngan nhat mang con: " << res << endl;
	delete[] arr;
	return 0;
}