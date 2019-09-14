#ifndef VK_API_H
#define VK_API_H

#include <string>
#include <unordered_map>
#include <vector>

#include "json.hpp"


namespace VK {
	using json = nlohmann::json;

	/* http params */
	using params_map = std::unordered_map<std::string, std::string>;

	class Client {
		private:
			static const std::string app_id;
			static const std::string app_secret;
			static const std::string scope;
			static const std::string auth_url;
			static const std::string api_url;
			std::string curl_buffer;

		protected:
			std::string version;
			std::string lang;
			std::string request(const std::string &url, const std::string &data);

		public:
			Client();
			json call(const std::string &params = "");
			virtual ~Client() {}
	};

	/* Network utils*/
	class Utils {
		public:
			static std::string data2str(const params_map &data);
			static std::string urlencode(const std::string &url);
			static std::string char2hex(const char dec);
			static int CURL_WRITER(char *data, size_t size, size_t nmemb, std::string *buffer);
	};
} // namespace VK
#endif // VK_API_H
