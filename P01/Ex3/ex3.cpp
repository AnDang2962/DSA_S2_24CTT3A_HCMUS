#include<iostream>
#include<string>

using namespace std;

void generateBinaryStrings(int n, string s) {
	if (n == 0) {
		cout << s << endl;
		return;
	}
	generateBinaryStrings(n - 1, s + "0");
	generateBinaryStrings(n - 1, s + "1");

}

int main(){ 
	int n; cin >> n;
	generateBinaryStrings(n, "");
	return 0;
}