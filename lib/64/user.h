#ifndef user_H
#define user_H

using namespace std;
#include  "items.h"

namespace VK {

	class User_1 :public  items //������������
	{
	private:
		/*��������*/
		string first_name;//���.
		string last_name;//�������.
		string deactivated;/*deleted-�������  ��� banned-�������������*/
		bool is_closed;//������� ����� 
		bool can_access_closed;//������� �����, �� ��� Acaunt ��� �����   
		/*��������������*/
	public:
		///////////////////////////////////////////////////
		//////////////////// ����������� //////////////////
		///////////////////////////////////////////////////

		User_1(items *pitem);

		///////////////////////////////////////////////////
		////////////// ����������� ���������� /////////////
		///////////////////////////////////////////////////

		template< typename T3,  typename T4> 
		vector<items>get
		(
			vector<items> *user_ids,//�������������� �������������
			vector<T3> *fields,//�������������� ����
			T4 *name_case);/*����� .  
						  ������������ � nom,
						  ����������� � gen,
						  ��������� � dat,
						  ����������� � acc,
						  ������������ � ins,
						  ���������� � abl.*/ 
		template<  typename T3> 
		vector<items> get
		(vector<items> user_ids,vector<T3> fields);
		vector<items> get
		(vector<items> user_ids);
		vector<items> get
		();


		///////////////////////////////////////////////////
		//////////////////// ���������� ///////////////////
		///////////////////////////////////////////////////

		template< typename T2, typename T3, typename T4>
		vector<items>getFollowers
		(
				items items, //������������� ������������
				size_t offset,//��������
				size_t count,//���������� �����������
				vector<T3> fields,//�������������� �����
				T4 name_case);/*����� .  
							  ������������ � nom,
							  ����������� � gen,
							  ��������� � dat,
							  ����������� � acc,
							  ������������ � ins,
							  ���������� � abl.*/
		template<typename T3>vector<items>getFollowers(items bases,size_t offset,size_t count,vector<T3> fields);
		vector<items>getFollowers(items basess, size_t offset, size_t count);
		vector<items>getFollowers(items basess, size_t offset);
		vector<items>getFollowers(items basses);
		vector<items>getFollowers();

		///////////////////////////////////////////////////
		///////////////////// ��������     ////////////////
		///////////////////////////////////////////////////
		template<typename T3>vector<items> getSubscriptions(
			items items, //�������������
			
			size_t offset,//��������
			T3 field,//�������������� ����� 
			size_t count,//����������
			bool extended);//1 � ������������ 0 �   ����� � ������������� ��������
		template<typename T3>
		vector<items> getSubscriptions(items items, size_t offset, T3 field);
		template<typename T3>
		vector<items> getSubscriptions(items items, size_t offset);
		template<typename T3>
		vector<items> getSubscriptions(items items);
		template<typename T3>
		vector<items> getSubscriptions();

		///////////////////////////////////////////////////
		////////////////////// ������  ////////////////////
		///////////////////////////////////////////////////

		template<typename T3>
		bool report(
				items user_id,//�������������
				string type_complaint,/*��� ������
												porn� �����������;
												spam� �������� �����;
												insult� �������������� ���������;
												advertisment� ���������, ���������� �����.*/
				string comment);//�����������
		template<typename T3>
		bool report(items user_id, string type_complaint);
		template<typename T3>
		bool report();
		///////////////////////////////////////////////////
		///////////////////   �����  //////////////////////
		///////////////////////////////////////////////////
		template<typename T3>
		vector<items> search(
					string q,//��������� �������
					bool sort,/*���������� �����������.	
										1 � �� ���� �����������;
										0 � �� ������������*/
					size_t offset,//�������� 
					size_t count,//���������� �������������
					string fields,//�������������� ����
					size_t  city,//������������� ������
					size_t icountry,//������������� ������
					string,//�������� ������ �������
					size_t university_country,/*������������� ������,
											  � ������� ������������ ��������� ���*/
					size_t university,//������������� ����
					size_t university_year,//��� ��������� ����
					size_t university_faculty,//������������� ����������
					size_t university_chair,//������������� �������
					size_t sex,/*���.
								   1 � �������;
								   2 � �������;
								   0 � �����(�� ���������)*/
					size_t status,/*�������� ���������:
										  1 � �� �����(�� �������);
										  2 � �����������;
										  3 � ���������(-�);
										  4 � �����(�������);
										  5 � �� ������;
										  6 � � �������� ������;
										  7 � �������(-�);
										  8 � � ����������� �����*/
					size_t,//�������, ��
					size_t age_to,//�������, ��
					size_t birth_day,//���� ��������
					size_t  birth_month,//����� ��������
					size_t  birth_year,//1900> ��� ��������  >2100
					bool online,/*�������.
										1 � ������ ������ ������������� ������;
										0 � ������ �� ���� �������������.*/
					bool has_photo,/*������� ����.
													1 � � �����������;
													0 � ���.*/
					size_t school_country,/*������������� ������ �����*/
					size_t school_city,/*������������� ������  �����*/
					size_t school_class,/*����� ������*/
					size_t school,/* ������������� �����*/
					size_t school_year,//��� ��������� �����
					string religion,//����������� �������
					string interests,//��������
					string company,//�������� �������� ��������
					string position,//�������� ���������
					size_t  group_id,//������������� ������
					string from_list);/*������� Acaunt ����� �������
										   friends � ����� ������;
										   subscriptions � ����� ������ � �������� */
				
				
				
			


		//~User_1();
		
	

	};

	

} //namespace VK

#endif
