#include <iostream>
#include <pqxx/pqxx>
#include <windows.h>
#undef min
#undef max

#pragma execution_character_set()

// ��� �����, ������� ������ ������� ��� �������� ������������ ���������� � �������
// � ��������� ������� � ���������� �� ����� ���� �� ������
// ������� clients ������ ���������� ����� �������(��� id), ��� ���. �������, ����������� �����
// ������� telephones ������ id ������ � �����(�_ ��������(��) �������  
void create_tables_if_not_exists(pqxx::connection& c)
{
	pqxx::transaction t(c);
	t.exec(
		"Create table if not exists clients"
		"("
		"id serial primary key,"
		"first_name text not null,"
		"last_name text not null,"
		"email text not null"
		");"
		"Create table if not exists telephones"
		"("
		"id serial primary key,"
		"clients_id integer references clients(id),"
		"number int"
		");"
	);
	t.commit();
}

// �����, ����������� �������� ������ �������

void add_new_client(pqxx::connection& c)
{
	// ��������, ������ � �� ���������� � �� �������, �� ������.
	std::string first_name;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Enter clients first name: ";
	
	std::getline(std::cin, first_name);

	std::string last_name;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Enter clients last name: ";
	std::getline(std::cin, last_name);

	std::string email;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Enter clients email: ";
	std::getline(std::cin, email);

	pqxx::transaction t(c);
	t.exec("insert into clients(first_name, last_name, email) values('" + first_name + "',  '" + last_name + "',  '" + email + "')");

	t.commit();
}

// �����, ����������� �������� ������� ������������� �������

void add_new_telephone_number(pqxx::connection& c)
{
	//������ �������� ���������
	std::string id_of_client;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Enter client id: ";
	std::getline(std::cin, id_of_client);
	

	std::string telephone_number;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Enter clients telephone number: ";
	std::getline(std::cin, telephone_number);

	pqxx::transaction t(c);

	t.exec("insert into telephones(clients_id, number) values('" + id_of_client + "', '" + telephone_number + "')");

	t.commit();
}

// �����, ����������� �������� ������ �������

void change_clients_data(pqxx::connection& c)
{
	// ������ �������� ���������
	
	std::string id_of_client;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Enter clients id: ";
	std::getline(std::cin, id_of_client);
	

	std::string first_name;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Enter clients first name: ";
	std::getline(std::cin, first_name);

	std::string last_name;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Enter clients last name: ";
	std::getline(std::cin, last_name);

	std::string email;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Enter clients e-mail: ";
	std::getline(std::cin, email);

	pqxx::transaction t(c);

	t.exec("update clients set first_name = '" + first_name + "', last_name = '" + last_name + "', email = '" + email + "' where id = '" + id_of_client + "'; ");

	t.commit();
}

// �����, ����������� ������� ������� � ������������� �������
// ���� ����� ��������, ���� � ������� ������ ���� �������. ����� �������, ����� ����� ������ ������� �� �����
void delete_telephone(pqxx::connection& c)
{
	// ������ �������� ���������
	
	std::string id_of_client;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Enter clients id of client, telephone number of whom you want delete: ";
	std::getline(std::cin, id_of_client);
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::string deleting_phone_number;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Enter telephone_number, which you want delete: ";
	std::getline(std::cin, deleting_phone_number);

	pqxx::transaction t(c);

	t.exec("delete from telephones where clients_id = '" + id_of_client + "' and number = '" + deleting_phone_number + "'; ");

	t.commit();
}

// �����, ����������� ������� ������������� �������, ����� 5
// ���� ����� ��������� 
void delete_client(pqxx::connection& c)
{
	std::string id_of_client;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Enter clients id of client, whom you want delete: ";

	std::getline(std::cin, id_of_client);
	

	pqxx::transaction t(c);

	t.exec("delete from telephones where clients_id = '" + id_of_client + "'; delete from clients where id = '" + id_of_client + "';" );
	t.commit();
}

// �����, ����������� ����� ������ ��� ������, ����� 6
// ����� ����� ������� �� ��� ������ - �����, �������, ����������� ����� ��� ��������.
// ����� ���� �� ��������
void find_client(pqxx::connection& c)
{

	std::string first_name;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Enter clients first name: ";
	std::getline(std::cin, first_name);

	
	std::string last_name;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Enter clients last name: ";
	std::getline(std::cin, last_name);

	std::string e_mail;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Enter clients e-mail: ";
	std::getline(std::cin, e_mail);

	std::string telephone_number;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Enter clients telephone number: ";
	std::getline(std::cin, telephone_number);

	pqxx::transaction t(c);
	//��� ������� ������� �� ������ 189 � ������� ��� ����� ���������. �� �������, ��� ������, �� ����� �� ����������?
	//Error: Tried to extract 0 field(s) from a result with 7 column(s).
	t.query("select * from clients where first_name like '" + first_name + "' or last_name like '" + last_name + "' or email like '" + e_mail + "'; "
		"select * from clients inner join telephones on clients.id = telephones.clients_id "
		"where number = '" + telephone_number + "';");

	t.commit();
}

int main()
{
	//setlocale(LC_ALL, "Russian");
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IOFBF, 1000);
	try {
		pqxx::connection c(
			"host=127.0.0.1 "
			"port=5432 "
			"dbname=dbPqxxProject002 "
			"user=postgres "
			"password=111111");

		// �������� �����, ������� ������ ��� ������� � ����������� � �������.
		create_tables_if_not_exists(c);
		// ����� ���� ����� ������ ��� ������� ������� ������ �������, ���� �� ��������.
		std::cout << "If you want add new client, print 1, if you want add telephone to client, print 2, "
			"if you want change client's data, print 3, if you want delete tel number of exist client, print 4, "
			"if you want delete exist client, print 5, if you want find client with his data print 6, "
			" if you want finished work, print 0" << std::endl;
		int a;
		std::cout << "You decision: ";
		std::cin >> a;
		if (a == 1)
		{
			// �������� �����, ������� ��������� ������ �������.
			add_new_client(c);
		}
		else if (a == 2)
		{
			// �������� �����, ������� ��������� �������� ������� �������
			add_new_telephone_number(c);
		}
		else if (a == 3)
		{
			// �������� �����, ������� ��������� �������� ������ � �������
			change_clients_data(c);
		}
		else if (a == 4)
		{
			// �������� �����, ������� ��������� ������� ������� � ������������� �������
			delete_telephone(c);
		}
		else if (a == 5)
		{
			// �������� �����, ����������� ������� ������������� �������
			delete_client(c);
		}
		else if (a == 6)
		{
			//�������� �����, ����������� ����� ������� �� �������, �����, ����������� ����� ��� ��������
			find_client(c);
		}
		else
		{
			std::cout << "Finished work, good buy" << std::endl;
		}

		std::cout << "Good bye" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	return 0;
}