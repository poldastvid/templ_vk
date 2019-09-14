
//#include <stdio.h>
#include <iostream>
#include "src/api.h"
#include "src/json.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>
#include <locale>

using namespace std;

void dom(string name) {
	VK::Client client_1;
	client_1.call(name);
}





 
string str1(string str);
string str2(string str);

void razdel(string str_buf, int i, int k, string rez_in ="", string str_base= "abcdefghijklmnopqrstuvwxyz0123456789_"){
	string v;
	
	if (str_buf == "*") str_buf = str_base;
	if (str_buf.length()!=1 ) {
		if(rez_in.length() < 2){
			thread t1(razdel,str1(str_buf),i, k, rez_in, str_base);
			//cout << "-";
			t1.detach();
			thread t2(razdel, str2(str_buf), i+(str_buf.length() / 2) + (str_buf.length() % 2),k, rez_in, str_base);
			//cout << "|";
			t2.detach();
		}
		else {
			//cout << "+";
			razdel(str1(str_buf), i, k, rez_in, str_base);
			razdel(str2(str_buf), i + (str_buf.length() / 2) + (str_buf.length() % 2), k, rez_in, str_base);
		}
		
		
	}else { 
		//cout << "*";
		rez_in = rez_in + str_buf;
		//cout << rez_in+ "	\n";
		if (rez_in.length() > 2) { dom(rez_in); cout << "(" + rez_in + " \n";}

		//cout <<i << endl;
		if (--k) {
			thread t3(razdel, "*", (i*str_base.length()) + 1, k, rez_in, str_base);
			t3.detach();
		}

	}
	
}


int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Russian");
	std::cout << "Количество потоков =" << std::thread::hardware_concurrency() << std::endl;
	string dpo;
	cin >> dpo;
	razdel("*",1,12345);
	

	cin >> dpo;
}



string str2(string str) {

	return str.substr((str.length() / 2) + (str.length() % 2)); // Строка после разделителя.

}

string str1(string str) {
	return str.substr(0, str.length() / 2 + (str.length() % 2));// первая часить строки.
}
/*
void gol(string rez_in, string str, int j, int k) {
	int i = 0;
	string rez_out;
	while (str[i] != NULL) {
		rez_out = rez_in + str[i];

		if (k < 0) { work(((j * 100) + i), rez_out); }
		i++;
		if (j > 0) { thread t1(gol, rez_out, str, --j, --k); t1.detach(); if (str[i] != NULL) { cout << ((j * 100) + i) << endl; } }
	}

}*/