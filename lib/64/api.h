#ifndef wiktoplaz_H
#define wiktoplaz_H

#include <string>
#include <unordered_map>
#include <vector>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;
using http_params = unordered_map<string, string>;

namespace wiktoplaz {
	namespace api {
		namespace proxy6 {
			class Error
			{
			private:
				//Client client_error;
			protected:
				size_t error_id;//-Номер ошибки;
				string error_mes;//Описание ошибки.
				http_params error_list;
			public:
				void set_error_id(int &i);
				string get_error_mes();
				int error_reh(const string &method, const http_params &data, const string &rez);
				int parse_error(const string &recuest, const string &method, const http_params &data);
			};

			class country {
			private:
			public:
				string name;
				int count;
				//доступном кол - во прокси для страны;

				void getcount(
					string country, ///-(Обязательный)-Код страны в формате iso2;
					int version ///- Версия прокси : 4 - IPv4, 3 - IPv4 Shared, 6 - IPv6(по - умолчанию).
					///Вывод count - Доступное кол - во. count_country
				);
			};

			class proksy_item {
			private:
				int id;/// - Внутренний номер прокси, необходим для продления срока действия - метод prolong
				string ip;///- IPv4, либо IPv6 скрытый за host : port - зависит от версии прокси;
				string host;/// - IPv4;
				int port;///- Порт;
				string user;/// - Логин;
				string pass;///- Пароль;
				string type;/// - Тип прокси : http - HTTPS, socks - SOCKS5;
				string country;/// - Страна(iso2);
				string date;/// - Дата покупки прокси;
				string date_end;/// - Дата окончания срока действия прокси;
				size_t unixtime;/// " : 1466379159,
				size_t unixtime_end;/// : 1468349441,
				string descr;/// - Технический комментарий;
				bool active;///  - Активный(1) или нет(0).

			protected:
			public:


			};

			

			class proxy6 {
			protected:
				
			private:
				string l_error;
				string curl_buffer;
				static const string app_secret;
				static const string api_url;
				string user_id;///Номер вашего аккаунта;
				double balance;///Текущее состояние вашего баланса;
				string currency;///Валюта вашего аккаунта (RUB, либо USD).
				vector<country> countrys;///список стран
				http_params params_temp;///временная переменная параметров запроса
				string metod_temp;///временная переменная метода запроса
				double getprice_price;/// -Итоговая стоимость;
				double getprice_price_single;///-Стоимость одного прокси;
				int getprice_period;///-Запрошенный период(кол - во дней);
				int getprice_count;///-Запрошенное кол - во прокси.


			public:
				Error error;
				//выводит одну страну в строчку
				string get_countrys_item(int i);//
				//выводит все страны в вектор строк
				vector<country> get_countrys_all();
				//выводит все страны в консоль
				void get_c_countrys_all();
				int base_parser(string &recuest);

				////возможности сервиса////

					//списка доступных стран;
				void getcountry(
					int	version/// - Версия прокси : 4 - IPv4, 3 - IPv4 Shared, 6 - IPv6(по - умолчанию).
					///list - Массив доступных стран в формате iso2. list_country
				);



				////покупка////

					//- Покупка прокси;
				vector<proksy_item> buy(
					int count,/// - (Обязательный)-Кол - во прокси для покупки;
					int period, ///- (Обязательный)-Период на который покупаются прокси - кол - во дней;
					string country, ///- (Обязательный)-Страна в формате iso2;
					int version, ///- Версия прокси : 4 - IPv4, 3 - IPv4 Shared, 6 - IPv6(по - умолчанию);
					string type,///- Тип прокси(протокол) : socks, либо http(по - умолчанию);
					string descr, ///- Технический комментарий для списка прокси, максимальная длина 50 символов.Указание данного параметра позволит вам делать выборку списка прокси про этому параметру через метод getproxy
					string auto_prolong, ///- При добавлении данного параметра(значение не требуется), у купленных прокси будет включено автопродление;
					string nokey/// - При добавлении данного параметра(значение не требуется), список list будет возвращаться без ключей.
					///Вывод  list_count - Кол - во прокси;list - Массив прокси->list_proksy_items
				);

				//- сумма заказа;
				void getprice(
					int	count,/// - (Обязательный)-Кол - во прокси;
					int   period,/// - (Обязательный)-Период - кол - во дней;
					int version/// - Версия прокси : 4 - IPv4, 3 - IPv4 Shared, 6 - IPv6(по - умолчанию).
					///Вывод:price,price_single,period,count
				);

				////управление////

					//- списка ваших прокси;
				vector<proksy_item> getproxy(
					string state = "", ///- Состояние возвращаемых прокси.Доступные значения : 
												///active - Активные, 
												///expired - Неактивные, 
												///expiring - Заканчивающиеся, 
												///all - Все(по - умолчанию);
					string descr = "",/// Технический комментарий, который вы указывали при покупке прокси.
					string nokey = ""/// - При добавлении данного параметра(значение не требуется), список list будет возвращаться без ключей.
					///Вывод  list_count - Кол - во прокси;list - Массив прокси->list_proksy_items
				);
				//- Продление списка прокси;
				vector<proksy_item> prolong(
					int period,/// - (Обязательный)-Период продления - кол - во дней;
					string ids,/// - (Обязательный)-Перечень внутренних номеров прокси в нашей системе, через запятую;
					string nokey/// - При добавлении данного параметра(значение не требуется), список list будет возвращаться без ключей.
					///Вывод  list_count - Кол - во прокси;list - Массив прокси->list_proksy_items
				);
				//- Удаление прокси;
				void delete_proksy(
					string ids,/// - (Обязательный)-Перечень внутренних номеров прокси в нашей системе, через запятую;
					string descr/// - (Обязательный)-Технический комментарий, который вы указывали при покупке прокси, либо через метод setdescr.
					///Обязательно должен присутствовать один из параметров, либо ids, либо descr.
					///count - Кол - во удаленных прокси.
				);
				//- Проверка валидности прокси.
				void check(
					string ids// - (Обязательный)-Внутренний номер прокси в нашей системе.

					///proxy_id - Внутренник номер прокси;
					///proxy_status - Результат проверки : true или false.
				);
				//- Изменение типа(протокола) прокси;
				void settype(
					string ids,/// - (Обязательный)-Перечень внутренних номеров прокси в нашей системе, через запятую;
					string type/// - (Обязательный)-Устанавливаемый тип(протокол) : http - HTTPS, либо socks - SOCKS5.
					///Вывод Error или сообщение по умолчанию
				);
				//- Обновление технического комментария;
				void setdescr(
					string new_,/// - (Обязательный)-Технический комментарий, на который нужно изменить.Максимальная длина 50 символов;
					string ids,/// - Перечень внутренних номеров прокси в нашей системе, через запятую.
					string old/// - Технический комментарий, который нужно изменить;
					///Обязательно должен присутствовать один из параметров, либо ids, либо old.
					///Вывод count - Кол - во прокси у которых был изменен комментарий.

				);


				///////////////////////выполнение запросов///////////////

				string call(const string &method, const params_map &params);
				string call(const string &method, const string &params = "");
				virtual ~Client() {}
			};

		} 
	}
	namespace 
}


#endif // wiktoplaz_H
