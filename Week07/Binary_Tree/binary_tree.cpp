#include<iostream>
#include<vector>
#include<stack>
#include<string>
#include<queue>
using namespace std;

struct Node {
	int key;
	Node* p_left; 
	Node* p_right;
};

//1. Hàm taọ node mới 
Node* createNode(int data) {
	Node* newNode = new Node();
	newNode->key = data;
	newNode->p_left = nullptr;
	newNode->p_right = nullptr;
	return newNode;
}

// 2. Hàm duyệt cây Pre-order 
vector<int> NLR(Node* root) {
	vector<int> res;
	if (root == nullptr) {
		return res;
	}
	stack<Node*> s; // mượn stack để chứa node 
	s.push(root); // đẩy vào để stack không bị rôngx ngay từ đầu 
	while (!s.empty()) {
		Node* temp = s.top(); // node phụ  
		res.push_back(temp->key); // đẩy vào vector kết quả 
		s.pop(); // xóa top ;


		if (temp->p_right != nullptr) {
			s.push(temp->p_right);
		} // đẩy con phải trước để con trái là node top để xét ở vòng while tiếp theo 

		if (temp->p_left != nullptr) {
			s.push(temp->p_left);
		}
	}
	return res;
}

//3. Hàm duyệt cây In_order: 
vector<int> LNR(Node* root){
	vector<int> res; 
	if (root == nullptr) {
		return res;
	}
	stack<Node*> s; // stack chứa node 
	Node* temp= root; // 1 node phụ để duyệt cây 
	while (temp != nullptr || !s.empty()) {
		while (temp != nullptr) { // khi node phụ ko null thì ta cứ việc đẩy các phần tử bên trái vào stack
			s.push(temp);
			temp = temp->p_left; // đẩy các node trái vào stack 
		}
		// khi temnp null và stack ko rỗng thì ra xử lí các phầntử có trong stack 
        Node* top = s.top();
		res.push_back(top->key); 
		s.pop();

		if (top != nullptr) {
			temp = top->p_right; // duyệt đêns con bên phải 
		}
	}
	return res;
}

// Hàm phụ để duyệt NRL 
vector<int> NRL(Node* root) {
	vector<int> res;
	stack<Node*> s; 
	if (root == nullptr) {
		return res;
	}
	s.push(root);
	while (!s.empty()) {
		Node* temp = s.top(); // node phụ xử lí top 
		res.push_back(temp->key);
		s.pop(); // xóa top 

		if (temp->p_left != nullptr) {
			s.push(temp->p_left); // đẩy con trái vào stack
		}
		if (temp->p_right != nullptr) {
			s.push(temp->p_right); // đẩy con phải 
		}
	}
	return res;
}

// 4.hàm theo Post_order 
vector<int> LRN(Node* root) {
	vector<int> res = NRL(root);

	// đâor ngược NRL để có LRN 
	reverse(res.begin(), res.end()); 
	return res;
}

// 5. Hàm duyệt cây theo level order 
vector<vector<int>> LevelOrder(Node* root) {
	vector<vector<int>> res; // ma trận kết quả 
	queue<Node*> q; // queue chứa node 
	if (root == nullptr) {
		return res; 
	}
	q.push(root); // đẩy gốc vào queue để không rỗng 
	while (!q.empty()) { 
		int SizeofLevel = q.size(); // số lượng node trong 1 level sẽ là các phần tử đang có trong q
		// tạo 1 vector để chứa các phần tử trong 1 level
		vector<int> levelN; 
		for (int i = 0; i < SizeofLevel; i++) {
			Node* temp = q.front(); // node phụ lấy ra phần tử đầu của q 
			levelN.push_back(temp->key);
			q.pop(); 
			// thêm các phần tử con bậc kế vào queue: 
			if (temp->p_left != nullptr) {
				q.push(temp->p_left);
			}
			if (temp->p_right != nullptr) {
				q.push(temp->p_right); 
			}

		}
		
		res.push_back(levelN); 
	}
	return res;
}

//6. Hàm đếm node của cây 
int countNode(Node* root) {
	int res = 0; 
	if (root == nullptr) return 0;
	
	return res =1+ (countNode(root->p_left) + countNode(root->p_right));
}

//7. Hàm đếm tổng các node trong cây 
int sumNode(Node* root) {
	int res = 0; 
	if (root == nullptr) return 0;
	return res = root->key + sumNode(root->p_left) + sumNode(root->p_right);
}

// Hàm tính chiều cao của cây
int heightTree(Node* root) {
	if (root == nullptr) {
		return -1; // cây rỗng 
	}
	//if (root->p_left == nullptr && root->p_right == nullptr) return 0; // cây 1 node 
	return 1 + max(heightTree(root->p_left), heightTree(root->p_right)); 
}

// Hàm dùng đệ quy tìm node trong cây 
Node* findNode(Node* root, int value) {
	if (root == nullptr) return nullptr;
	if (root->key == value) return root;

	Node* res_left = findNode(root->p_left, value); // tìm bên trái 
	if (res_left != nullptr) return res_left;

	Node* res_right = findNode(root->p_right, value); // tìm bên phải 
	if (res_right != nullptr) return res_right;
}

//8.Hàm để tính chièu cao của 1 node trong cây : 
int heightNode(Node* root, int value) { // tìm được node trong cây rồi gọi hàm tính height 
	if (root == nullptr) {
		return -1; 
	}
	
	//tìm node trong cây
	Node* node = findNode(root, value); // tìm node 

	//tính bậc của node 
	if (node == nullptr) return -1;
	int res = heightTree(node); // tính chiều cao node ;
	return res;
}



//9. Hàm tính level của 1 node trong cây 
int Level(Node* root, Node* p) {
	if (root == nullptr) return -1; // rỗng 
	if (root == p) return 0; // tìm thấy node p

	int left_res = Level(root->p_left, p);
	if (left_res != -1) return left_res + 1;  // nêus vẫn chưa đến null thì cứ tiếp tục xét trái 

	int right_res = Level(root->p_right, p);  // tiếp tục xét phải 
	if (right_res != -1) return right_res + 1 ;

	return -1; // không tìm thấy 
}

//10, Hàm đếm số node lá trong cây 

bool isLeaf(Node* root) {
	if (root->p_left != nullptr || root->p_right != nullptr) return false;
	return true;
}

int countLeaf(Node* root) {
	if (root == nullptr) return 0; // rỗng 
	int res = 0; 
	if (isLeaf(root)) return 1;
	else {
		res += countLeaf(root->p_left) + countLeaf(root->p_right); 
	}
	return res;
}
