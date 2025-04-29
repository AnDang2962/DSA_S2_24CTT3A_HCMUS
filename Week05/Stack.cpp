#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
using namespace std;

struct NODE {
	int key;
	NODE* p_next;
};

struct Stack {
	NODE* top;
};

NODE* createNode(int key) {
	NODE* newNode = new NODE();		
	newNode->key = key;
	newNode->p_next = nullptr;
	return newNode;
}

Stack* initializeStack() {
	Stack* newStack = new Stack();
	newStack->top = nullptr;
	return newStack;
}

void push(Stack*& s, int  key) {
	NODE* newNode = createNode(key);
	newNode->p_next = s->top;
	s->top = newNode;
}

int pop(Stack*& s) {
	if (s->top == nullptr) {
		cout << "Stack is empty " << endl; 
		return -1;
	}
	NODE* temp = s->top; 
	int val = temp->key;
	s->top = s->top->p_next;
	delete temp;
	return val;
}

int size(Stack s) {
	int cnt = 0;
	NODE* temp = s.top;
	while (temp != nullptr) {
		cnt++;
		temp = temp->p_next;
	}
	return cnt;
}

bool isEmpty(Stack *s) {
	if (s->top ==  nullptr) {
		return true;
	}
	else {
		return false;
	}
}

//void printStack(Stack *s) {
//	NODE* temp = s->top;
//	while (temp != nullptr) {
//		cout << temp->key << " ";
//		temp = temp->p_next;
//	}
//}


void processFile(string& inputfile, string&outputfile) {
	ifstream infile(inputfile); 
	ofstream outfile(outputfile);
	if (!infile.is_open()) {
		cout << "Error: cannot open inputfile" << endl;
		return;
	}
	if (!outfile.is_open()) {
		cout << "Error: cannot open outputfile" << endl;
		return;
	}
	string line; 
	Stack* s = nullptr;
	while (getline(infile, line)) {
		stringstream ss(line);
		string command;
		ss >> command;
		if (command == "init") {
			s = initializeStack();
			outfile << "Stack is initialize- Empty" << endl;
		}
		else if (command == "push") {
			if (s == nullptr) { // chưa khởi tạo stack		
				outfile << "Stack is not initialized" << endl;
			}
			int key; 
			ss >> key;
			push(s, key);
			NODE* temp = s->top;
			vector<int> elements;
			while (temp != nullptr) {
				elements.push_back(temp->key);
				temp = temp->p_next;
			}
			for (int i = elements.size() - 1; i >= 0; i--) {
				outfile << elements[i] << " ";
			}
			outfile << endl;
		}
		else if (command == "pop") {
			if (isEmpty(s)== true) {
				outfile << "EMPTY" << endl;
			}else if (s == nullptr) { // chưa khởi tạo stack		
				outfile << "Stack is not initialized" << endl;
			}
			else {
				pop(s);
				if (isEmpty(s)) {
					outfile << "EMPTY" << endl;
				}
				else {
					NODE* temp = s->top;
					vector<int> elements;
					while (temp != nullptr) {
						elements.push_back(temp->key);
						temp = temp->p_next;
					}
					for (int i = elements.size() - 1; i >= 0; i--) {
						outfile << elements[i] << " ";
					}
					outfile << endl;
				}
			}
		}
		else {
			outfile << "Command not found" << endl;
		}
	}
	cout << "File processed successfully!" << endl;
}


int main() {
	string inputfile = "input.txt";
	string outputfile = "output.txt";
	processFile(inputfile, outputfile);
	return 0;
}
