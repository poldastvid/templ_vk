#include "api.h"
#define CURL_STATICLIB
#include "curl/curl.h"


#ifdef _DEBUG
#	pragma comment (lib,"curl/libcurl_a_debug.lib")
//#pragma comment (lib, "openssl.lib")
#	pragma comment (lib, "ws2_32.lib")
#	pragma comment (lib, "wldap32.lib")
#   pragma comment (lib, "crypt32.lib")
#   pragma comment (lib, "normaliz.lib")
#   pragma comment (lib, "Advapi32.lib")
#pragma comment (lib, "openssl/lib/libcryptoMTd.lib")
#pragma comment (lib, "openssl/lib/libsslMTd.lib")
#else
#	pragma comment (lib,"curl/libcurl_a.lib")
#	pragma comment (lib, "ws2_32.lib")
#	pragma comment (lib, "wldap32.lib")
#   pragma comment (lib, "crypt32.lib")
#   pragma comment (lib, "normaliz.lib")
#   pragma comment (lib, "Advapi32.lib")

#endif
using ::std::string;
using json = ::nlohmann::json;
using namespace std;
const string  proxy6::Client::api_url = "https://proxy6.net/api/fa80c7ae61-63d0b0e086-3f2246522d/";//стандартный путь 
const string  proxy6::Client::app_secret = "VeWdmVclDCtn6ihuP1nt";// android=hHbZxrka2uZ6jB1inYsH




std::string proxy6::Client::call(const string &method, const string &params) {
    if(method.empty()) {
		
        return nullptr;
    }
	
    string url = api_url + method;
    string data = params + ( (params.empty()) ? "" : "&");
	return  request(url, data);
    
}

//Перегрузка функции сall преобразует params_map в string
std::string proxy6::Client::call(const string &method, const params_map &params) {
    if(method.empty()) {
        return nullptr;
    }
	
    string data;
    if(params.size()) {
        data = proxy6::Utils::data2str(params);
    }
	this->params_temp = params;
	this->metod_temp = method;
    return this->call(method, data);
}
//Заменяет символы на %...
string proxy6::Utils::char2hex(const char dec) {
    char dig1 = (dec & 0xF0) >> 4;
    char dig2 = (dec & 0x0F);

    if (0  <= dig1 && dig1 <=  9) dig1 += 48;
    if (10 <= dig1 && dig1 <= 15) dig1 += 87;
    if (0  <= dig2 && dig2 <=  9) dig2 += 48;
    if (10 <= dig2 && dig2 <= 15) dig2 += 87;

    string r;
    r.append(&dig1, 1);
    r.append(&dig2, 1);
    return r;
}
//Проверяет строку на символы если они естьто заменяет %...
string proxy6::Utils::urlencode(const string &url) {

    string escaped;
    for(const char& c : url) {
        if ( (48 <= c && c <= 57)  ||
             (65 <= c && c <= 90)  ||
             (97 <= c && c <= 122) ||
             (c =='~' || c =='!' || c =='*' || c =='(' || c ==')' || c =='\'')
             ) {
            escaped.append( &c, 1);
        } else {
            escaped.append("%");
            escaped.append( char2hex(c) );
        }
    }

    return escaped;
}
//подготавливают url из  params_map
string proxy6::Utils::data2str(const params_map &data) {
    string result;
    for(auto &kv:data) {
        result += kv.first + "=" + urlencode(kv.second)+ "&";
    }

    return result;
}
//функций к VK на CURL
int proxy6::Utils::CURL_WRITER(char *data, size_t size, size_t nmemb, string *buffer) {
    int result = 0;
    if (buffer != NULL) {
        buffer->append(data, size * nmemb);
        result = size * nmemb;
    }

    return result;
}
//запрос к VK на CURL
string proxy6::Client::request(const string &url, const string &data) {
    static char errorBuffer[CURL_ERROR_SIZE];
    curl_buffer.clear();

    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "VK API Client");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, proxy6::Utils::CURL_WRITER);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curl_buffer);

        CURLcode result = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if (result == CURLE_OK) {
            return curl_buffer;
        } else {
            return errorBuffer;
        }
    }
    curl_easy_cleanup(curl);

    return "";
}

string proxy6::Client::get_countrys_item(int i)
{
	int i_1 = 0;
	for (auto position = this->countrys.begin(); position != this->countrys.end(); ++position) {
		if (i_1 == i) { return (*position).name;}
	}
	return "";
}

vector<proxy6::country> proxy6::Client::get_countrys_all()
{
	return this->countrys;
}

void proxy6::Client::get_c_countrys_all() {
	int i_1 = 0;
	for (auto position = this->countrys.begin(); position != this->countrys.end(); ++position) {
		std::cout << (*position).name << "|" << (i_1++) << " \n";///выведем то,что получилось.
	}
}
int proxy6::Client::base_parser(std::string &recuest)
{
	try {
		json item = json::parse(recuest);
		if (item.find("error") != item.end()) {
			return this->error.parse_error(recuest, this->metod_temp, this->params_temp);
		}
		else {
			this->user_id = item.at("user_id").get<string>();
			this->balance = atof((item.at("balance").get<string>()).c_str());
			this->currency = item.at("currency").get<string>();
			return 1;
		}
	}
	catch (...) {
		return this->error.parse_error(recuest, this->metod_temp, this->params_temp);
	}

}

void proxy6::Client::getcountry(int version)
{
	params_map params{
		{"version" , std::to_string(version)}
	};
	string recuest=this->call("getcountry", params);///запрос с методом getcountry к api с params-параметрами
	//парсим общую часть ответа и проверяем ответ на ошибки. После этого парсим частную ответа 
	if((this->base_parser(recuest)) == 1){///парсер общей части
		json json_rec = json::parse(recuest);///переводим запрос из str
		//парсим частный отет
		json json_rec_list = json_rec.at("list").get<json>();///парсер вытаскиваем список list из отета
		this->countrys.clear();///очищаем список стран
		proxy6::country country_temp;///создаем временнную переменную с типом странны в нее будем складывать все странны поочередно
		for (auto position = json_rec_list.begin(); position != json_rec_list.end(); ++position) {
			country_temp.name = position.value().get<string>();///Складываем значения во временную переменную
			this->countrys.push_back(country_temp);///парсер список list в переменную country
		}
		
	}
}



std::vector<proxy6::proksy_item> proxy6::Client::buy(int count, int period, string country, int version, string type, string descr, string auto_prolong, string nokey)
{
	return std::vector<proksy_item>();
}

void proxy6::Client::getprice(int count, int period, int version)
{
}

void proxy6::Error::set_error_id(int &i)
{
	this->error_id = i;
}

string proxy6::Error::get_error_mes()
{
	return this->error_mes;
}
//Решение ошибки
int proxy6::Error::error_reh(const string &method, const params_map &data, const string &rez)
{
	this->error_list = data;
	std::cout <<"ERORR"<< rez;
	return -1;
}

int proxy6::Error::parse_error(const string &recuest, const string &method, const params_map &data)
{
	try {
		json json_item = json::parse(recuest);
		this->error_id = json_item.at("error_id").get<int>();
		this->error_mes = json_item.at("error").get<float>();
		return this->error_reh(method, data, recuest);
	}
	catch (...) {
		return this->error_reh(method, data, recuest);
	}
}

void proxy6::country::getcount(string country, int version)
{

}
