
//#include <stdio.h>
#include <iostream>
#include <vector>
#include "src/user.h"
#include "src/json.hpp"
#include <windows.h>
#include <fstream>
using namespace std;

string fa2_callback();

string captcha_callback(const string &captcha_sid);

int print_man(int &argc, char *argv[],
	string &access_token, string &login, string &pass);

int print_time(size_t i) {
	
	string s1;
	//s1= ToString(id)+"user.txt";
	s1 = "log.txt";
	ofstream fout(s1, ios_base::app);
	if (!fout.is_open()) // если файл небыл открыт
	{
		cout << "Файл не может быть открыт или создан\n"; // напечатать соответствующее сообщени
		return 0;
		 // выполнить выход из программы
	}
	
		SYSTEMTIME st;
		GetLocalTime(&st);
		fout <<"id:	"<< i <<"|"<<st.wYear << "|" << st.wMonth << "|" << st.wDay << "|	" << st.wHour << "|" << st.wMinute << "|" << st.wSecond << "|" << st.wMilliseconds<< "|" << endl;
		fout.close();

};


int main(int argc, char *argv[]) {
	
	
	
	string access_token, login, pass;
	cout << "login:" << endl;
	cin >> login;
	cout << "password" << endl;
	cin >> pass;
	
	//print_man(argc=3, argv,access_token, login, pass);
    VK::Client api;
    api.set_fa2_callback(fa2_callback);
    api.set_cap_callback(captcha_callback);
    if(api.auth(login, pass, access_token)) {
       
		cout << "Auth ok" << endl;
        cout << "Access token: " << api.access_token() << endl;
		cout << "Bot1:"<<endl;
		
			print_time(0);

		

		VK::items irems1;
		irems1.id = 1;
		VK::User_1 f(&irems1);
		f.client = &api;
		for (size_t i = 1; i < 510666315; i+=1000)
		{
			f.id = i;
			f.get();
			for (size_t j = 10; j < 510666315; j = j * 10) {
				if ((i % j) == 1 & i < j*10) {
					print_time(i);
				};	
			}
		}
		string r1;
		cin>> r1;
		
    } else {
        cout << "Auth fail: " << api.last_error() << endl;
    }

    return 0;
}


string fa2_callback() {
	string res;
	cout << "Enter 2fa code: ";
	cin >> res;
	return res;
}

string captcha_callback(const string &captcha_sid) {
	string res;

	cout << "Open image https://api.vk.com/captcha.php?sid=" << captcha_sid;

	string res2 = "https://api.vk.com/captcha.php?sid=" + captcha_sid;

	cout << " and enter text: " << endl;
	cin >> res;
	return res;
}

int print_man(int &argc, char *argv[], string &access_token, string &login, string &pass) {
	if (argc < 2 || argc > 4) {
		cout << "Usage: [access_token] login pass" << endl;
		return 1;
	}



	if (argc == 2) {
		access_token = argv[1];
	}
	else if (argc == 3) {
		login = argv[1];
		pass = argv[2];

	}
	else if (argc == 4) {
		access_token = argv[1];
		login = argv[2];
		pass = argv[3];

	}
	else {
		cout << "Usage: [access_token] login pass" << endl;
		return 1;
	}
	return 0;
}
