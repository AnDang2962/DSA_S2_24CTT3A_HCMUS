#include<iostream>
#include<string>

using namespace std; 

void generateBinaryStrings(int n, string s) {
	if (s.length() == n) {
		cout << s << endl;
		return;
	}
	generateBinaryStrings(n , s + '0');
	generateBinaryStrings(n , s + '1');
}

int main() {
	int n; cin >> n;
	generateBinaryStrings(n, "");
	return 0;
}