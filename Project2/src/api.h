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
				size_t error_id;//-����� ������;
				string error_mes;//�������� ������.
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
				//��������� ��� - �� ������ ��� ������;

				void getcount(
					string country, ///-(������������)-��� ������ � ������� iso2;
					int version ///- ������ ������ : 4 - IPv4, 3 - IPv4 Shared, 6 - IPv6(�� - ���������).
					///����� count - ��������� ��� - ��. count_country
				);
			};

			class proksy_item {
			private:
				int id;/// - ���������� ����� ������, ��������� ��� ��������� ����� �������� - ����� prolong
				string ip;///- IPv4, ���� IPv6 ������� �� host : port - ������� �� ������ ������;
				string host;/// - IPv4;
				int port;///- ����;
				string user;/// - �����;
				string pass;///- ������;
				string type;/// - ��� ������ : http - HTTPS, socks - SOCKS5;
				string country;/// - ������(iso2);
				string date;/// - ���� ������� ������;
				string date_end;/// - ���� ��������� ����� �������� ������;
				size_t unixtime;/// " : 1466379159,
				size_t unixtime_end;/// : 1468349441,
				string descr;/// - ����������� �����������;
				bool active;///  - ��������(1) ��� ���(0).

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
				string user_id;///����� ������ ��������;
				double balance;///������� ��������� ������ �������;
				string currency;///������ ������ �������� (RUB, ���� USD).
				vector<country> countrys;///������ �����
				http_params params_temp;///��������� ���������� ���������� �������
				string metod_temp;///��������� ���������� ������ �������
				double getprice_price;/// -�������� ���������;
				double getprice_price_single;///-��������� ������ ������;
				int getprice_period;///-����������� ������(��� - �� ����);
				int getprice_count;///-����������� ��� - �� ������.


			public:
				Error error;
				//������� ���� ������ � �������
				string get_countrys_item(int i);//
				//������� ��� ������ � ������ �����
				vector<country> get_countrys_all();
				//������� ��� ������ � �������
				void get_c_countrys_all();
				int base_parser(string &recuest);

				////����������� �������////

					//������ ��������� �����;
				void getcountry(
					int	version/// - ������ ������ : 4 - IPv4, 3 - IPv4 Shared, 6 - IPv6(�� - ���������).
					///list - ������ ��������� ����� � ������� iso2. list_country
				);



				////�������////

					//- ������� ������;
				vector<proksy_item> buy(
					int count,/// - (������������)-��� - �� ������ ��� �������;
					int period, ///- (������������)-������ �� ������� ���������� ������ - ��� - �� ����;
					string country, ///- (������������)-������ � ������� iso2;
					int version, ///- ������ ������ : 4 - IPv4, 3 - IPv4 Shared, 6 - IPv6(�� - ���������);
					string type,///- ��� ������(��������) : socks, ���� http(�� - ���������);
					string descr, ///- ����������� ����������� ��� ������ ������, ������������ ����� 50 ��������.�������� ������� ��������� �������� ��� ������ ������� ������ ������ ��� ����� ��������� ����� ����� getproxy
					string auto_prolong, ///- ��� ���������� ������� ���������(�������� �� ���������), � ��������� ������ ����� �������� �������������;
					string nokey/// - ��� ���������� ������� ���������(�������� �� ���������), ������ list ����� ������������ ��� ������.
					///�����  list_count - ��� - �� ������;list - ������ ������->list_proksy_items
				);

				//- ����� ������;
				void getprice(
					int	count,/// - (������������)-��� - �� ������;
					int   period,/// - (������������)-������ - ��� - �� ����;
					int version/// - ������ ������ : 4 - IPv4, 3 - IPv4 Shared, 6 - IPv6(�� - ���������).
					///�����:price,price_single,period,count
				);

				////����������////

					//- ������ ����� ������;
				vector<proksy_item> getproxy(
					string state = "", ///- ��������� ������������ ������.��������� �������� : 
												///active - ��������, 
												///expired - ����������, 
												///expiring - ���������������, 
												///all - ���(�� - ���������);
					string descr = "",/// ����������� �����������, ������� �� ��������� ��� ������� ������.
					string nokey = ""/// - ��� ���������� ������� ���������(�������� �� ���������), ������ list ����� ������������ ��� ������.
					///�����  list_count - ��� - �� ������;list - ������ ������->list_proksy_items
				);
				//- ��������� ������ ������;
				vector<proksy_item> prolong(
					int period,/// - (������������)-������ ��������� - ��� - �� ����;
					string ids,/// - (������������)-�������� ���������� ������� ������ � ����� �������, ����� �������;
					string nokey/// - ��� ���������� ������� ���������(�������� �� ���������), ������ list ����� ������������ ��� ������.
					///�����  list_count - ��� - �� ������;list - ������ ������->list_proksy_items
				);
				//- �������� ������;
				void delete_proksy(
					string ids,/// - (������������)-�������� ���������� ������� ������ � ����� �������, ����� �������;
					string descr/// - (������������)-����������� �����������, ������� �� ��������� ��� ������� ������, ���� ����� ����� setdescr.
					///����������� ������ �������������� ���� �� ����������, ���� ids, ���� descr.
					///count - ��� - �� ��������� ������.
				);
				//- �������� ���������� ������.
				void check(
					string ids// - (������������)-���������� ����� ������ � ����� �������.

					///proxy_id - ���������� ����� ������;
					///proxy_status - ��������� �������� : true ��� false.
				);
				//- ��������� ����(���������) ������;
				void settype(
					string ids,/// - (������������)-�������� ���������� ������� ������ � ����� �������, ����� �������;
					string type/// - (������������)-��������������� ���(��������) : http - HTTPS, ���� socks - SOCKS5.
					///����� Error ��� ��������� �� ���������
				);
				//- ���������� ������������ �����������;
				void setdescr(
					string new_,/// - (������������)-����������� �����������, �� ������� ����� ��������.������������ ����� 50 ��������;
					string ids,/// - �������� ���������� ������� ������ � ����� �������, ����� �������.
					string old/// - ����������� �����������, ������� ����� ��������;
					///����������� ������ �������������� ���� �� ����������, ���� ids, ���� old.
					///����� count - ��� - �� ������ � ������� ��� ������� �����������.

				);


				///////////////////////���������� ��������///////////////

				string call(const string &method, const params_map &params);
				string call(const string &method, const string &params = "");
				virtual ~Client() {}
			};

		} 
	}
	namespace 
}


#endif // wiktoplaz_H
