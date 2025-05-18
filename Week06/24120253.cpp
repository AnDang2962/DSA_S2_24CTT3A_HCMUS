#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;

struct Company {
	string name;
	string profit_tax;
	string address;
};

struct Node {
	Company data; 
	Node* next;
};

struct HashTable {
	static const int SIZE = 2000; // kích thước của bảng băm 
	Node* table[SIZE]; // mảng 2000 phần tử, mỗi phần tử là 1 con trỏ đến đầu danh sách liên kết 
};

// Hàm để đọc dữ liệu từ file
vector<Company> readfile(string filename) {
	ifstream file(filename);
	if (!file.is_open()) {
		cout << "Can not open file " << filename << endl;
	}
	vector<Company> companies;
	string line; 
	
	// bỏ qua dòng tiêu đề đầu tiên 
	getline(file, line); 

	// đọc từng dòng 
	while (getline(file, line)) {
		stringstream ss(line); 
		string name, tax, addr;
		getline(ss, name, '|'); // lấy từ đầu dòng đến dấu '|' 
		getline(ss, tax, '|');//lấy đến '|' tiếp theo 
		getline(ss, addr); // lấy hết dòng
		// mượn biến phụ để ghi vào mảng 
		Company temp;
		temp.name = name;
		temp.profit_tax = tax;
		temp.address = addr;
		companies.push_back(temp); 
	}
	file.close(); 
	return companies; 
}



// Hàm băm chuỗi tên của công ty 
long long hashString(string company_name) {
	long long hash_value = 0;
	int p = 31;
	int m = 2000;
	string temp;
	long long power = 1; 
	int len = company_name.length(); 
	if (len <= 20) {
		 temp = company_name;
	}
	else {
		 temp = company_name.substr(len - 20, 20); // lấy 20 kí tự cuối
	}
	
	// tính toán 
	for (int i = 0; i < temp.length(); i++) {
		hash_value = (hash_value + int(temp[i]) * power) % m ;
		power = (power * p) % m; // tăng bậc p lên 31 
	}

	return hash_value; 
}

// Hàm tạo bẳng băm 
HashTable* createHashTable(vector<Company> list_company) {
	HashTable* newHashTable = new HashTable;
	// khơir tạo mỗi phần tử đầu của mỗi ô là nullptr ;
	for (int i = 0; i < 2000; i++) {
		newHashTable->table[i] = nullptr;
	}
	int size = list_company.size(); // số lượng công ty 
	for (int i = 0; i < size; i++) {
		long long hash_val = hashString(list_company[i].name); // tính được hash_value từ tên cong ty 
		// tạo node mới để luuw thông tin công ty 
		Node* newNode = new Node;
		newNode -> data = list_company[i];
		newNode->next = nullptr;

		// xử lí ghi vào bảng băm 
		if (newHashTable->table[hash_val] == nullptr) {// nếu còn trống 
			newHashTable->table[hash_val] = newNode; 
		}
		else { // nếu có thì xử lí đụng độ, chèn vào đầu danh sách liên kết 
			newNode->next = newHashTable->table[hash_val];
			newHashTable->table[hash_val] = newNode;
		}
	}
	return newHashTable; 
}

// Hàm để thêm 1 công ty khác vào bảng: 
void insert(HashTable* hashTable, Company company) {
	// lấy 20 kí tự cuối 
	int len = company.name.length(); 
	string temp = "";
	if (len <= 20) {
		temp = company.name;
	}
	else {
		temp = company.name.substr(len - 20, 20); 
	}
	long long hash_val = hashString(temp); 
	if (hashTable->table[hash_val] == nullptr) {
		Node* newNode = new Node;
		newNode->data = company;
		newNode->next = nullptr;

		hashTable->table[hash_val] = newNode;
	}
	else {
		Node* newNode = new Node;
		newNode->data = company;
		newNode->next = nullptr;

		newNode->next = hashTable->table[hash_val];
		hashTable->table[hash_val] = newNode;
	}
}

//Hàm để tìm kiếm 1 công ty 
Company* search(HashTable* hashTable, string company_name) {
	
	// lấy 20 kí tự cuối 
	int len = company_name.length();
	string temp = "";
	if (len <= 20) {
		temp = company_name;
	}
	else {
		temp = company_name.substr(len - 20, 20);
	}
	long long hash_val = hashString(temp);
	// truy cập và duyẹt danh sách 
	if (hashTable->table[hash_val] == nullptr) {
		return nullptr; // không tìm thấy 
	}
	else {
		Node* current = hashTable->table[hash_val]; 
		while (current != nullptr) {
			if (current->data.name == company_name) {
				return &current->data;
				
			}
			current = current->next;
		}
		return nullptr;
	}
}

// đọc được file mst.txt , file input.txt cho thao tác chèn và tìm kiếm để in ra file output.txt 

int main(int argv, char* argc[]) {
	if (argv != 4) {
		cout << "Usage: ./24120253.exe <MST.txt> <input.txt> <output.txt>" << endl;
		return 1;
	}
	string mst_file = argc[1];
	vector<Company> list_company = readfile(mst_file); // đọc file mst 
	ifstream inputfile(argc[2]); // file inp
	ofstream outputfile(argc[3]); //outp

	if (!inputfile.is_open()) {
		cout << "Cannot open file " << argc[2] << endl;
		return 1;
	}
	if (!outputfile.is_open()) {
		cout << "Cannot oen file " << argc[3] << endl;
		return 1;
	}
	
	HashTable* hashTable = createHashTable(list_company); // tạo bảng băm cho list trong mst 

	// Đọc file input để tìm kiếm thông tin công ty từ tên 
	string line; // đọc tên công ty vào line 
	Company* res = nullptr;
	while (getline(inputfile, line)) { // đọc từng dòng
		res = search(hashTable, line); 
		if (res != nullptr) {
			outputfile << res->name << "|" << res->profit_tax << "|" << res->address << endl;
		}
		else {
			outputfile << "not found" << endl;
		}
	}
	inputfile.close();
	outputfile.close();
	cout << "Done !!! " << endl;

	// Giải phóng bộ nhớ của linkedlist
	for (int i = 0; i < hashTable->SIZE;i++) {
		Node* current = hashTable->table[i];
		while (current != nullptr) {
			Node* temp = current;
			current = current->next;
			delete temp; // giair phòng node 
		}
	}
	delete hashTable; // giải phóng bảng băm
	return 0;
}


