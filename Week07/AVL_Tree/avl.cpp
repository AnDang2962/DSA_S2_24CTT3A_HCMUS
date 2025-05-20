#include<iostream>
#include<vector>
#include<stack>
#include<queue> 

using namespace std;

struct Node {
	int key;
	Node* p_left;
	Node* p_right;
	int height;
};

//1. hàm tạo node mới : 
Node* createNode(int data) {
	Node* newNode = new Node();
	newNode->key = data;
	newNode->p_left = nullptr;
	newNode->p_right = nullptr;
	newNode->height = 0; // chiều cao của 1 node mới là 0  
	return newNode;
}

//2. Hàm để chèn thêm 1 node vào cây AVL: 
//Cần các hàm xoay để -> cân bằng sau khi chèn  

// Hàm tính chiều cao 1 node: 
int height(Node* root) { // trong struct có biến height 
	if (root == nullptr) return -1; // rỗng 
	else {
		return root->height;
	}
}

// Hàm cập nhật height của node sau khi xoay: 
int updateHeight(Node* root) {
	if (root == nullptr) return -1; // rỗng 
	else {
	return 	root->height = max(height(root->p_left), height(root->p_right)) + 1; // lấy chiều cao cao nhất của 1 trong 2 nhánh dưới cộng 1 là ra node đang xét
	}
	
}

// Hàm tính độ cân bằng của 1 node: 
int balence(Node* root) {
	if (root == nullptr) return 0; // cx là cây cân bằng 
	else {
		return height(root->p_left) - height(root->p_right); // chênh lệch cây trái và phải 
	}
}

//hàm xoay trái :  xoay đơn thì xoay cách node cân bằng 1 bậc 
Node* rotateLeft(Node* root) {
	Node* newRoot = root->p_right; // tạo node gốc mới là con phải của root cũ 
	root->p_right = newRoot->p_left; // root ở bên dưới newRoot nên ko còn là cha của newRoot 

	newRoot->p_left = root; // gán lại root trở thành con trái newRoot ;

	updateHeight(root);  // phải cập nhật root trước vì nó gần lá hơn 
	updateHeight(newRoot);
	return newRoot; 
}

// Hàm xoay phải : 
Node* rotateRight(Node* root) {
	Node* newRoot = root->p_left; 
	root->p_left = newRoot->p_right; // không còn là cha con 

	newRoot->p_right = root; // gán lại cha con 

	updateHeight(root);
	updateHeight(newRoot);
	return newRoot;
}

// Hàm xoay kép trái_phải: 
Node* rotateLeftRight(Node* root) {
	Node* newRoot = rotateLeft(root->p_left) ; // xoay kép thì ta phải xoay node cách node mâts cân bằng 2 bậc 
	Node* newRoot2 = rotateRight(newRoot);
	return newRoot2; 
}

Node* rotateRightLeft(Node* root) {
	Node* newRoot = rotateRight(root->p_right);
	Node* newRoot2 = rotateLeft(newRoot);
	return newRoot2; 
}

// 2.Hàm chèn node vào cây AVL : 
void Insert(Node*& root, int x) {
	Node* newNode = createNode(x);
	if (root == nullptr) {
		root = newNode;
		
	}
	if (root->key == x) return; // node đã có trong cây
	else if (root->key < x) {
		Insert(root->p_right, x); // đệ quy chèn phải 
	}
	else if (root->key > x) {
		Insert(root->p_left, x); // đệ quy chèn trái 
	}

	// chèn xong thì câp nhật độ cao 
	updateHeight(root);

	// Kiểm tra độ cân bằng: 
	int bal = balence(root);
	if (bal > 1 && x < root->p_left->key) { // lệch sang trái nên xoay phải 
		root = rotateRight(root);
	}
	else if (bal < -1 && x> root->p_right->key) { // lệch sang phải 
		root = rotateLeft(root);
	}
	else if (bal < -1 && x < root->p_right->key) { // lệch phải trái 
		root = rotateRightLeft(root); 
	}
	else if (bal > 1 && x > root->p_left->key) {// lệch trái phải 
		root = rotateLeftRight(root);
	}
}

//3. hàm xóa node trong cây 
void Remove(Node*& root, int x) { // tìm được node, rồi có 3 trường hợp xóa, xong mới cân bằng 
	if (root == nullptr) return; // rỗng 
	if (root->key < x) {
		Remove(root->p_right, x);
	}
	else if (root->key > x) {
		Remove(root->p_left, x);
	}
	else { // tìm thấy 
		if (root->p_left == nullptr && root->p_right == nullptr) { // xóa lá 
			delete root;
			root = nullptr;
		}
		else if (root->p_right == nullptr && root->p_left != nullptr) { // xóa node  1 con 
			Node* temp = root;
			root = root->p_left;
			delete temp;
			temp = nullptr;
		}
		else if (root->p_left == nullptr && root->p_right != nullptr) { // xóa node 1 con 
			Node* temp = root; 
			root = root->p_right;
			delete temp; 
			temp = nullptr;
		}
		else { // xóa node 2 con 
			// tìm node lớn nhất bên trái 
			Node* temp = root->p_left;
			while (temp->p_right != nullptr) { // tìm node lớn nhất bên trái 
				temp = temp->p_right;
			}
			root->key = temp->key; // cập nhật lại key cho node cần xóa
			Remove(root->p_left, temp->key); // đệ quy xóa node lớn nhất bên trái
		}
	}
	// cập nhật chiều cao 
	updateHeight(root);
	// Kiểm tra cân bằng : 
	int bal = balence(root);
	if (bal > 1) { // cây bị lệch sang trái 
		if (balence(root->p_left) >= 0) { 
			rotateRight(root); 
	    }
		else { // nhánh con bị lệch phải 
		 rotateLeftRight(root);
		}
	}
	else if (bal < -1) { //cây lệch phải 
		if (balence(root->p_right) <= 0) { // cây con bị lệch phải 
			rotateLeft(root);
		}
		else { // cây con bị lệch trái 
			rotateRightLeft(root);
		}
	}
 }


// Hàm check phải cây BST không: 
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

//4. hàm check cây AVL:
bool checkAVL(Node* root) { // là cây nhị phân nhưng có thêm điều kiện độ lệch <=1 
	if (root == nullptr) return true; // rỗng 
	int bal = balence(root);
	if (bal > 1 || bal < -1) return false; // lệch quá thì ko phải AVL 
	return checkAVL(root->p_left) && checkAVL(root->p_right); // đệ quy kiểm tra các nhánh con 
}

bool isAVL(Node* root) {
	return checkAVL(root) && isBST(root);
}


