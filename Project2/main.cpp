
//#include <stdio.h>
#include <iostream>
#include "src/api.h"
#include "src/json.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <windows.h>
using namespace std;
void dom(string name) {
	VK::Client client_1;
	client_1.call(name);
}
int password_user() {
	string s; 
	ifstream file("user.txt");
	while (getline(file, s)) { dom(s); }
	file.close();
	return 1;
}
int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Russian");
	int dpo;
	cout << "Привет \n";
	cout << "{password_user"<< password_user() <<"password_user}\n";
	cin >> dpo;
}

