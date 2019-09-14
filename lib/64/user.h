#ifndef user_H
#define user_H

using namespace std;
#include  "items.h"

namespace VK {

	class User_1 :public  items //ѕользователи
	{
	private:
		/*ќсновные*/
		string first_name;//им€.
		string last_name;//фамили€.
		string deactivated;/*deleted-удалена  или banned-заблокирована*/
		bool is_closed;//профиль скрыт 
		bool can_access_closed;//профиль скрыт, но его Acaunt его видит   
		/*ƒополнительные*/
	public:
		///////////////////////////////////////////////////
		//////////////////// конструктор //////////////////
		///////////////////////////////////////////////////

		User_1(items *pitem);

		///////////////////////////////////////////////////
		////////////// расширенна€ информацию /////////////
		///////////////////////////////////////////////////

		template< typename T3,  typename T4> 
		vector<items>get
		(
			vector<items> *user_ids,//идентификаторы пользователей
			vector<T3> *fields,//дополнительные пол€
			T4 *name_case);/*падеж .  
						  именительный Ц nom,
						  родительный Ц gen,
						  дательный Ц dat,
						  винительный Ц acc,
						  творительный Ц ins,
						  предложный Ц abl.*/ 
		template<  typename T3> 
		vector<items> get
		(vector<items> user_ids,vector<T3> fields);
		vector<items> get
		(vector<items> user_ids);
		vector<items> get
		();


		///////////////////////////////////////////////////
		//////////////////// подписчики ///////////////////
		///////////////////////////////////////////////////

		template< typename T2, typename T3, typename T4>
		vector<items>getFollowers
		(
				items items, //идентификатор пользовател€
				size_t offset,//смещение
				size_t count,//количество подписчиков
				vector<T3> fields,//дополнительных полей
				T4 name_case);/*падеж .  
							  именительный Ц nom,
							  родительный Ц gen,
							  дательный Ц dat,
							  винительный Ц acc,
							  творительный Ц ins,
							  предложный Ц abl.*/
		template<typename T3>vector<items>getFollowers(items bases,size_t offset,size_t count,vector<T3> fields);
		vector<items>getFollowers(items basess, size_t offset, size_t count);
		vector<items>getFollowers(items basess, size_t offset);
		vector<items>getFollowers(items basses);
		vector<items>getFollowers();

		///////////////////////////////////////////////////
		///////////////////// подписки     ////////////////
		///////////////////////////////////////////////////
		template<typename T3>vector<items> getSubscriptions(
			items items, //идентификатор
			
			size_t offset,//смещение
			T3 field,//дополнительные полей 
			size_t count,//количество
			bool extended);//1 Ц объединенный 0 Ц   групп и пользователей отдельно
		template<typename T3>
		vector<items> getSubscriptions(items items, size_t offset, T3 field);
		template<typename T3>
		vector<items> getSubscriptions(items items, size_t offset);
		template<typename T3>
		vector<items> getSubscriptions(items items);
		template<typename T3>
		vector<items> getSubscriptions();

		///////////////////////////////////////////////////
		////////////////////// жалоба  ////////////////////
		///////////////////////////////////////////////////

		template<typename T3>
		bool report(
				items user_id,//идентификатор
				string type_complaint,/*тип жалобы
												pornЧ порнографи€;
												spamЧ рассылка спама;
												insultЧ оскорбительное поведение;
												advertismentЧ рекламна€, засор€юща€ поиск.*/
				string comment);//комментарий
		template<typename T3>
		bool report(items user_id, string type_complaint);
		template<typename T3>
		bool report();
		///////////////////////////////////////////////////
		///////////////////   поиск  //////////////////////
		///////////////////////////////////////////////////
		template<typename T3>
		vector<items> search(
					string q,//поисковой запроса
					bool sort,/*сортировка результатов.	
										1 Ч по дате регистрации;
										0 Ч по попул€рности*/
					size_t offset,//смещение 
					size_t count,//количество пользователей
					string fields,//дополнительные пол€
					size_t  city,//идентификатор города
					size_t icountry,//идентификатор страны
					string,//название города строкой
					size_t university_country,/*идентификатор страны,
											  в которой пользователи закончили ¬”«*/
					size_t university,//идентификатор ¬”«а
					size_t university_year,//год окончани€ ¬”«а
					size_t university_faculty,//идентификатор факультета
					size_t university_chair,//идентификатор кафедры
					size_t sex,/*пол.
								   1 Ч женщина;
								   2 Ч мужчина;
								   0 Ч любой(по умолчанию)*/
					size_t status,/*семейное положение:
										  1 Ч не женат(не замужем);
										  2 Ч встречаетс€;
										  3 Ч помолвлен(-а);
										  4 Ч женат(замужем);
										  5 Ч всЄ сложно;
										  6 Ч в активном поиске;
										  7 Ч влюблен(-а);
										  8 Ч в гражданском браке*/
					size_t,//возраст, от
					size_t age_to,//возраст, до
					size_t birth_day,//день рождени€
					size_t  birth_month,//мес€ц рождени€
					size_t  birth_year,//1900> год рождени€  >2100
					bool online,/*Ђонлайнї.
										1 Ч искать только пользователей онлайн;
										0 Ч искать по всем пользовател€м.*/
					bool has_photo,/*Ќаличие фото.
													1 Ч с фотографией;
													0 Ч все.*/
					size_t school_country,/*идентификатор страны школы*/
					size_t school_city,/*идентификатор города  школы*/
					size_t school_class,/*буква класса*/
					size_t school,/* идентификатор школы*/
					size_t school_year,//год окончани€ школы
					string religion,//религиозные взгл€ды
					string interests,//интересы
					string company,//название компании работают
					string position,//название должности
					size_t  group_id,//идентификатор группы
					string from_list);/*–азделы Acaunt через зап€тую
										   friends Ч среди друзей;
										   subscriptions Ч среди друзей и подписок */
				
				
				
			


		//~User_1();
		
	

	};

	

} //namespace VK

#endif
