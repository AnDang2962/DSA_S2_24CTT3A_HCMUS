#include<iostream>

using namespace std; 

void TowerOfHaNoi(int n, char from_rod, char to_rod, char temp_rod) { // còn 1 đĩa cuối thì đi từ đầu sang đích
	if (n == 1) {
		cout << "Move disk 1 from " << from_rod << " to " << to_rod << endl;
		return;
	}
	TowerOfHaNoi(n - 1, from_rod, temp_rod, to_rod);// đi từ đầu qua trung gian, lấy cột đích làm trung gian
		cout << "Move disk " << n << " from " << from_rod << " to " << to_rod << endl;
	TowerOfHaNoi(n - 1, temp_rod, to_rod, from_rod); // đi từ trung gian sang đích, cột đích làm trung gian
}

int main() {
	int n; cin >> n; // số lượng đĩa 
	TowerOfHaNoi(n, 'A', 'C', 'B');
	return 0;
}