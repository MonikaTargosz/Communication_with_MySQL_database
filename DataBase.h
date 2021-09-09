#pragma once

#include <my_global.h>
#include <mysql.h>
#include <iostream>

using namespace std;

class DataBase
{
protected:
	MYSQL *con;

	void finish_with_error(MYSQL *con);

	MYSQL_RES *exec(char * q);

public:
	DataBase(char * host, char * usr, char * pwd, char * db);
	~DataBase();

	void print_query(char * q); // stdout in the class, so as not to make too many combinations (error checking will also output the text)
	
	int check_login(char * login, char * pwd);
};
