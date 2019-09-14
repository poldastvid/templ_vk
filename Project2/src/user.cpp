#include  "items.h"
#include "user.h"
#include "iostream"
#include "vector"
#include <fstream>
#include <sstream>



using namespace std;

 

namespace VK{
	///////////////////////////////////////////////////
	//////////////////// конструктор //////////////////
	///////////////////////////////////////////////////

	template<typename T>
	string ToString(T t) {

		stringstream ss;

		ss << t;

		return ss.str();
	}

	User_1::User_1(items *pitem)
	{
		this->id = (*pitem).id;
	}
	

	///////////////////////////////////////////////////
	////////////// расширенная информацию /////////////
	///////////////////////////////////////////////////

	template<typename T3, typename T4>
	vector<items> User_1::get
	(vector<items> *user_ids, vector<T3> *fields, T4 *name_case)
	{

		return vector<items>();
	}
	

	template<typename T3> 
	vector<items> User_1::get
	(vector<items> user_ids, vector<T3> fields)
	{
		return vector<items>();
	}

	vector<items> User_1::get
	(vector<items> user_ids)
	{
		return vector<items>();
	}

	vector<items> User_1::get
	()
	{
		
		
		
		params_map params = {
		   {"user_ids", ToString(id)}
		};

		string s1;
		//s1= ToString(id)+"user.txt";
		s1= "user.txt";
		ofstream fout(s1, ios_base::app);
		if (!fout.is_open()) // если файл небыл открыт
		{
			cout << "Файл не может быть открыт или создан\n"; // напечатать соответствующее сообщение
			return vector<items>(); // выполнить выход из программы
		}

		json aa = this->client->call("users.get", params);
		//cout << aa << endl;
		aa=aa.at("response");

		aa = aa.begin().value();

		id= aa.at("id").get<size_t>();
		first_name = aa.at("first_name").get<string>();;
		last_name = aa.at("last_name").get<string>();;


 		//cout << "id:" << id  << "|first_name:" << first_name << "|last_name:" << last_name << endl;
		fout << id << "|" << first_name << "|" << last_name << endl;
		fout.close();
		return vector<items>();
	}
	
	///////////////////////////////////////////////////
	//////////////////// подписчики ///////////////////
	///////////////////////////////////////////////////

	template<typename T2, typename T3, typename T4>
	vector<items> User_1::getFollowers(items items, size_t offset, size_t count, vector<T3> fields, T4 name_case)
	{
		return vector<items>();
	}

	template<typename T3>
	vector<items> User_1::getFollowers(items bases, size_t offset, size_t count, vector<T3> fields)
	{
		return vector<items>();
	}

	vector<items> User_1::getFollowers(items basess, size_t offset, size_t count)
	{
		return vector<items>();
	}

	vector<items> User_1::getFollowers(items basess, size_t offset)
	{
		return vector<items>();
	}

	vector<items> User_1::getFollowers(items basses)
	{
		return vector<items>();
	}

	vector<items> User_1::getFollowers()
	{
		
		return vector<items>();
	}

	///////////////////////////////////////////////////
	///////////////////// подписки     ////////////////
	///////////////////////////////////////////////////

	template<typename T3>
	vector<items> User_1::getSubscriptions(items items, size_t offset, T3 field, size_t count, bool extended)
	{
		return vector<items>();
	}
	template<typename T3>
	vector<items> User_1::getSubscriptions(items items, size_t offset, T3 field)
	{
		return vector<items>();
	}
	template<typename T3>
	vector<items> User_1::getSubscriptions(items items, size_t offset)
	{
		return vector<items>();
	}
	template<typename T3>
	vector<items> User_1::getSubscriptions(items items)
	{
		return vector<items>();
	}
	template<typename T3>
	vector<items> User_1::getSubscriptions()
	{
		return vector<items>();
	}

	///////////////////////////////////////////////////
	////////////////////// жалоба  ////////////////////
	///////////////////////////////////////////////////

	template<typename T3>
	bool User_1::report(items user_id, string type_complaint, string comment)
	{
		return vector<items>();
	}
	template<typename T3>
	bool User_1::report(items user_id, string type_complaint)
	{
		return vector<items>();
	}
	template<typename T3>
	bool User_1::report()
	{
		return vector<items>();
	}
	
	
	///////////////////////////////////////////////////
	///////////////////   поиск  //////////////////////
	///////////////////////////////////////////////////

	template<typename T3>
	vector<items> VK::User_1::search(string q, bool sort, size_t offset,
		size_t count, string fields, size_t city, size_t icountry,
		string, size_t university_country, size_t university,
		size_t university_year, size_t university_faculty,
		size_t university_chair, size_t sex, size_t status, size_t, size_t age_to,
		size_t birth_day, size_t birth_month, size_t birth_year, bool online,
		bool has_photo, size_t school_country, size_t school_city, 
		size_t school_class, size_t school, size_t school_year, 
		string religion, string interest, string company, 
		string position, size_t group_id, string from_list)
	{
		return vector<items>();
	}

/*
	User_1::~User_1()
	{
	}*/
}

