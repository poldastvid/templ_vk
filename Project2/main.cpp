
//#include <stdio.h>

#include <windows.h>
#include <fstream>
#include <istream>
#include <iostream>
using namespace std;



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

		for (size_t i = 1; i < 510666315; i++)
		{
			for (size_t j = 10; j < 510666315; j = j * 10) {
				if ((i % j) == 0 & i < j*10) {
					print_time(i);
				};	
			}
		}
    return 0;
}

