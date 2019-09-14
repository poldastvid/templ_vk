#pragma once

class curl_client
{
public:
	curl_client();
	~curl_client();
};

string request(const string &url, const string &data);
/* Network utils
 */
class Utils {
public:
	static std::string data2str(const params_map &data);
	static std::string urlencode(const std::string &url);
	static std::string char2hex(const char dec);
	static int CURL_WRITER(char *data, size_t size, size_t nmemb, std::string *buffer);
};
