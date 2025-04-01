#include<iostream>
#include<vector>

using namespace std;

void InsertionSort(int arr[], int n) {

	for (int i = 1; i < n; i++) {
		int key = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j+1] = key;
	}
}

void Triplet(int arr[], int n) { // Săps xếp trước ròi sử dụng 2 con trỏ
	InsertionSort(arr, n);
	//Vòng for duyệt mảng với chỉ số i, với i là phần tử đầu trong bộ 3, dùng 2 con trỏ để tìm 2 phần tử trong phần còn lại của mảng 
	for (int i = 0; i < n; i++) {
		if (arr[i] > 0) break; // sau khi sắp xếp thì nếu tại arr[i] > 0 thì phía sau không có phần tử âm nào

		// Bỏ qua các giá trị trùng lặp của arr[i]
		if (i > 0 && arr[i] == arr[i - 1]) continue;

		int start = i + 1; // trỏ đầu
		int end = n - 1;  // trỏ cuối 
		
		while (start < end) {
			int sum = arr[i] + arr[start] + arr[end];
			if (sum > 0) {
				end--; // nếu sum > 0 thì ta cần giảm sum lại bằng cách lấy phần tử nhỏ hơn
			}
			else if (sum < 0) {
				start++; // ngược lại ta cần phần tử lớn hơn 
			}
			else {
				cout << arr[i] << " " << arr[start] << " " << arr[end] << endl;

				// Bỏ qua các giá trị trùng lặp của arr[start] và arr[end]
				while (start < end && arr[start] == arr[start + 1]) start++;
				while (start < end && arr[end] == arr[end - 1]) end--;

				// cập nhật chỉ số mới của cả 2 trỏ
				start++;
				end--;
			}
		}
	}
}

int main() {
	cout << "Nhap so luong phan tu; ";
	int n; cin >> n;
	int* arr = new int[n];
	cout << "Nhap mang: ";
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	cout << " Cac bo 3 thoa man: " << endl;
	Triplet(arr, n);
	return 0;
}