#include<iostream>
#include<vector>
#include<stack>
#include<queue>

using namespace std;

struct Node {
	int key;
	Node* p_left; 
	Node* p_right;
};

// Hàm tạo node mới 
Node* createNode(int data) {
	Node* newNode = new Node();
	newNode->key = data;
	newNode->p_left = nullptr;
	newNode->p_right = nullptr;
	return newNode;
}


//1. Hàm tìm node trong cây 
Node* Search(Node* root, int x) {
	if (root == nullptr) return nullptr; // cây rỗng 
	if (root->key == x) return root; // tìm thấy 
	if (x < root->key) return Search(root->p_left,x) ;
	else {
		return Search(root->p_right, x);
	}
}

//2. Hàm chèn node vào cây 
void Insert(Node*& root, int x) {
	Node* newNode = createNode(x); // tạo node 
	if (root == nullptr) { // cây rỗng thì node mới làm gốc 
		root = newNode; 
	}
	if (root->key == x) return; // nếu đã có node thì không chèn nữa
	if (x < root->key) {
		Insert(root->p_left, x); // qua trái để chèn 
	}
	else {
		Insert(root->p_right, x); // qua phải để chèn 
	}
}

//3. Hàm xóa 1 node trong cây 
void Remove(Node*&root, int x) { // có 3 case: xóa node lá, xáo node có 1 con, xóa node 2 con. 
	if (root == nullptr) return; // cây rỗng 
	if (root->key < x) {
		Remove(root->p_right, x);
	}
	else if (root->key > x) {
		Remove(root->p_left, x);
	}
	else {
		if (root->key == x) { // tìm được node cần xóa 
			if (root->p_left == nullptr && root->p_right == nullptr) { // case 1
				delete root;
				root = nullptr;
			}
			else if (root->p_left == nullptr || root->p_right == nullptr) { // case 2: giống linkedlist
				Node* temp = root; // node phụ 
				if (root->p_left != nullptr) {
					root = root->p_left; // cập nhật cây 

				}
				else if (root->p_right != nullptr) {
					root = root->p_right; // cập nhật cây 
				}
				delete temp; // xóa node 
			}
			else { // case 3: thay vì xóa trực tiếp thì ta tìm node Y thay thế node cần xóa 
				// tìm Y bằng 1 in 2 cách: trái nhất con phải or phải nhất con trái 
				Node* temp = root->p_left; // đi qua trái 
				while (temp->p_right != nullptr) {
					temp = temp->p_right; // tìm phải nhất 
				}  // sau vòng lặp temp là node phải nhất 
				root->key = temp->key; // cập nhật 
				Remove(root->p_left, temp->key); // đệ quy xóa node Y 
			}
		}
	}
}

//4. Hàm tạo cây từ mảng: 
Node* createTree(int a[], int n) {
	Node* root = nullptr; // tạo cây rỗng 
	for(int i = 0; i < n; i++) {
		Insert(root, a[i]); 
	}
	return root; 
}



// 5. Hàm xóa cây 
void removeTree(Node*& Root) {
	if (Root == nullptr) return; // cây rỗng 
	else {
		removeTree(Root->p_left); // xóa bên trái 
		removeTree(Root->p_right); // xóa bên phải 
		delete Root; // xóa node gốc 
		Root = nullptr; // cập nhật lại gốc 
	}
}


//6. hàm tính Height 
int Height(Node* root) {
	if (root == nullptr) {
		return -1; // cây rỗng 
	}
	
	return 1 + max(Height(root->p_left), Height(root->p_right)); 
}

//7. Đếm số node có key nhỏ hơn x ( input) trong cây:
int countLess(Node* root, int x ){
	if (root == nullptr) return 0;  // cây rỗng
	if (root->key > x) { // nếu key lớn hơn x thì đếm bên trái
		return countLess(root->p_left, x); 
	}
	else if (root->key == x) {
		return countLess(root->p_left, x);
	}
	else {
		return 1 + countLess(root->p_left, x) + countLess(root->p_right, x); // đã ở cây con nhỏ hơn x thì tính cả cây con đó 
	}
}
 

//8. Đếm số node có key lớn hơn x :
int countGreater(Node* root, int x) {
	if (root == nullptr) return 0; // rỗng 
	if (root->key < x) {
		return countGreater(root->p_right, x); // đi về phải 
	}
	else if (root->key == x) {
		return countGreater(root->p_right, x);
	}
	else {
		return 1 + countGreater(root->p_left,x) + countGreater(root->p_right,x);
	}
}

//9. Kiểm tra có phải cây BST không: 
// là BST thì khi xét theo In_order phải ra 1 mảng tăng dần . 

//Hàm duyệt In_order ;
vector<int> InOrder(Node* root) {
	vector<int> res;
	stack<Node*> s;
	if (root == nullptr) return res; // rỗng 
	Node* temp = root;
	while (temp != nullptr || !s.empty()) {
		while (temp != nullptr) { // lấy hết các node trái vào stack 
			s.push(temp);
			temp = temp->p_left;
		}

		// temp null và stack ko rroongx thì xử lí trong stackj 
		Node* top = s.top();
		res.push_back(top->key);
		s.pop();

		if (top != nullptr) {
			temp = top->p_right; // xét xong 1 node thì xét qua phải node đó 
		} 
	}
	return res;
}

bool isBST(Node* root) {
	vector <int> res = InOrder(root);
	for (int i = 0; i < res.size(); i++) {
		for (int j = i + 1; j < res.size(); j++) {
			if (res[i] > res[j]) return false;
 		}
	}
	return true;
}

//10. Kiểm tra có phải fullBST: 1) là  BST va 2) mỗi cha đều có đủ 2 con
bool isFullBST(Node* root) {
	if (root == nullptr) return true; 
	if (!isBST(root) ) return false;
	if (root->p_left != nullptr && root->p_right == nullptr) return false;
	if (root->p_left == nullptr && root->p_right != nullptr) return false; 
    // không dùng "||" vì như vậy mặc định sẽ là false vì cây luôn luôn có node lá  
	return isFullBST(root->p_left) && isFullBST(root->p_right); 
}



