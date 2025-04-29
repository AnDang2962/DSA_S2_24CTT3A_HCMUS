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

struct Queue {
	NODE* head; 
	NODE* tail;
};

NODE* createNode(int key) {
	NODE* newNode = new NODE();
	newNode->key = key;
	newNode->p_next = nullptr;
	return newNode;
}

Queue* initializeQueue() {
	Queue* newQueue = new Queue();
	newQueue->head = nullptr;
	newQueue->tail = nullptr;
	return newQueue;
}

void enqueue(Queue*& q, int key) {
	NODE* newNode = createNode(key); 
	if (q->head == nullptr || q->tail== nullptr) {
		q->head = newNode;
		q->tail = newNode;
	}
	else {
		q->tail->p_next = newNode;
		q->tail = newNode;
	}
}

int dequeue(Queue*& q) {
	if (q->head == nullptr || q->tail == nullptr) {
		cout << "Queue is empty " << endl;
	}
	else {
		NODE* temp = q->head;
		int val = temp->key;
		q->head = q->head->p_next;
		delete temp;
		if (q->head == nullptr) { // sau khi xóa queue trôngs 
			q->tail = nullptr;
		}
		return val;
	}
}

int size(Queue* s) {
	int cnt = 0; 
	NODE* temp = s->head;
	while (temp != nullptr) {
		cnt++;
		temp = temp->p_next;
	}
	return cnt;
}

bool isEmpty(Queue* q) {
	if (q->head == nullptr || q->tail == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

void processFile(string& inputfile, string &outputfile) {
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
	Queue* q = nullptr;
	while (getline(infile, line)) {
		stringstream ss(line);
		string command;
		ss >> command;
		if (command == "init") {
			q = initializeQueue();
			outfile << "Queue initialized- EMPTY" << endl;
		}
		else if (command == "enqueue") {
			if (q == nullptr) {
				outfile << "Queue is not initialized" << endl;
				
			}
			int key;
			ss >> key; 
			enqueue(q, key);
			NODE* temp = q->head;
			while (temp != nullptr) {
				outfile << temp->key << " ";
				temp = temp->p_next;
			}
			outfile << endl;
		}
		else if (command == "dequeue") {
			if (q == nullptr) {
				outfile << "Queue is not initialized" << endl;
			}
			else {
				if (isEmpty(q)) {
					outfile << "EMPTY" << endl;
				}
				else {
					dequeue(q);
					if (isEmpty(q)) {
						outfile << "EMPTY" << endl;
					}
					else {
						NODE* temp = q->head;
						while (temp != nullptr) {
							outfile << temp->key << " ";
							temp = temp->p_next;
						}
						outfile << endl;
					}
				}
			}
		}
		else {
			outfile << "Command not found" << endl;
		}
	}
	cout << "File process successfully" << endl;
}

int main() {
	string inputfile = "input.txt";
	string outputfile = "output.txt";
	processFile(inputfile, outputfile);
	return 0;
}

