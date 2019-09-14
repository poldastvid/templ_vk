#include "api.h"
#define CURL_STATICLIB
#include "curl/curl.h"
#include <fstream>
#include <sstream>
#include<set>
#include <thread>
/*
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

#endif*/

#ifdef _DEBUG
#pragma comment (lib,"curl/libcurl_a_debug.lib")
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
#	pragma comment (lib, "wldap64.lib")
#   pragma comment (lib, "crypt64.lib")
#   pragma comment (lib, "normaliz.lib")
#   pragma comment (lib, "Advapi64.lib")

#endif
using ::std::string;
using json = ::nlohmann::json;
using namespace std;
const string VK::Client::api_url = "https://mythicalworld.su/ajax.php";//стандартный путь 
/*const string VK::Client::app_id = "3140623";// android=2274003
const string VK::Client::app_secret = "VeWdmVclDCtn6ihuP1nt";// android=hHbZxrka2uZ6jB1inYsH*/

//Конструктор
VK::Client::Client(){ }

size_t counter(const string& s)
{
	set<char> c(s.begin(), s.end());
	return c.size();
}
//функуция обработки методов
json VK::Client::call(const string &name) {
		string params = "do=CheckName&name="+name+"&";

		if (request(api_url, params).length()==190) {
			ofstream fout("user.txt", ios_base::app);
			fout << name +"\n";
			fout.close();
		}
		//cout << "" + params + "\n";
		return nullptr;
		}
	



//Заменяет символы на %...
string VK::Utils::char2hex(const char dec) {
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
string VK::Utils::urlencode(const string &url) {

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
string VK::Utils::data2str(const params_map &data) {
    string result;
    for(auto &kv:data) {
        result += kv.first + "=" + urlencode(kv.second)+ "&";
    }

    return result;
}
//функций к VK на CURL
int VK::Utils::CURL_WRITER(char *data, size_t size, size_t nmemb, string *buffer) {
    int result = 0;
    if (buffer != NULL) {
        buffer->append(data, size * nmemb);
        result = size * nmemb;
    }

    return result;
}
//запрос к VK на CURL
string VK::Client::request(const string &url, const string &data) {
    static char errorBuffer[CURL_ERROR_SIZE];
    curl_buffer.clear();

    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "VK API Client");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, VK::Utils::CURL_WRITER);
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


