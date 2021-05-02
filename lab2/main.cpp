#include <iostream>
using namespace std;
#include"Header.h"
int main()
{
	string input;
	List newtree;
	cout << "Enter the string: ";
	getline(cin, input);
	newtree.insert(input);
	cout << "Enter the code: ";
	getline(cin, input);
	newtree.decryption(input);
	return 0;
}