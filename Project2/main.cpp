
//#include <stdio.h>
#include <iostream>
#include <vector>
#include "src/api.h"
#include "src/json.hpp"
#include <windows.h>
#include <fstream>
#include <thread>

using namespace std;





int main(int argc, char *argv[]) {
	
	proxy6::Client api;
	proxy6::params_map params{
		{"version","4"}
	};
	cout << api.call("getcountry", params) << "\n";
	api.getcountry(4);
	cout << "На данный момент вам доступны следующие странны: \n";
	api.get_c_countrys_all();
	cout << "Количество прокси в стране (введите id): \n";
	int id_contry;
	std::cin >> id_contry;
	api.getcount(api.get_countrys_item(id_contry), 4);

}
