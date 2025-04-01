#include<iostream>

using namespace std;

int leastWeightShip(int arr[], int n, int day) {
	// trọng lượng tối thiếu của tàu thì phải bằng gói hàng lớn nhất 
	// trọng lượng tối đa tàu có thể chở là tôngr tâtr cả 
	int low = arr[0];
	int high = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i] > low) {
			low = arr[i];
		}
		high += arr[i];
	}

	// Binary Search để tìm trọng tải tối thiểu
	while (low < high) {
		int mid = low + (high - low) / 2;
		int currentLoad = 0; // Tổng trọng lượng đang xét trong ngày hiện tại
		int requiredDays = 1; // Số ngày cần thiết (ít nhất là 1)

		// Mô phỏng quá trình chất hàng
		for (int i = 0; i < n; i++) {
			if (currentLoad + arr[i] > mid) {
				requiredDays++; // Tăng số ngày nếu vượt quá capacity
				currentLoad = arr[i]; // Reset trọng lượng ngày hiện tại
			}
			else {
				currentLoad += arr[i]; // Cộng dồn trọng lượng
			}
		}

		// Kiểm tra số ngày cần thiết
		if (requiredDays <= day) { // số ngày đi nhỏ hơn ngày cần nên trọng lựogn tàu vẫn còn có thể nhỏ hơn, để chở nhiều ngày hơn
			high = mid; // Giảm capacity để tìm giá trị nhỏ hơn
		}
		else { // số ngày đi lớn hơn tức là trọng lượng nhỏ nhất còn nhỏ nên không đủ chở thỏa mãn số ngayf cần
			low = mid + 1; // Tăng capacity nếu không đủ ngày
		}
	}
	return low; // Kết quả là trọng tải tối thiểu
}


int main() {
	cout << "Nhap so luong goi hang: ";
	int n; cin >> n;
	int* arr = new int[n];
	cout << "Nhap can nang cac goi hang: ";
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	cout << "Nhap so ngay: ";
	int day; cin >> day;
	cout << "Trong luong nho nhat cua tau thoa de bai: ";
	cout << leastWeightShip(arr, n, day) << endl;
	return 0;
}