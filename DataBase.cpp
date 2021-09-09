#include "DataBase.h"


DataBase::DataBase(char * host, char * usr, char * pwd, char * db)
{
	con = mysql_init(NULL);

	if (con == NULL)
	{
		cout << "mysql_init() failed\n";
		exit(1);
	}

	if ( mysql_real_connect(con, host, usr, pwd, db, 0, NULL, 0) == NULL )
	{
		finish_with_error(con);
	}

}


DataBase::~DataBase()
{
	mysql_close(con);
}


void DataBase::finish_with_error(MYSQL *con)
{

	cout << mysql_error(con) << endl;
	mysql_close(con);
	system("pause");
	exit(1);
}

void DataBase::print_query(char * q)
{
	MYSQL_RES *result = exec(q);

	int num_fields = mysql_num_fields(result);

	MYSQL_ROW row;

	while ((row = mysql_fetch_row(result)))
	{
		for (int i = 0; i < num_fields; i++)
		{
			printf("%s ", row[i] ? row[i] : "NULL");
		}
		printf("\n");
	}

	mysql_free_result(result);

}

MYSQL_RES* DataBase::exec(char * q)
{
	if (mysql_query(con, q))
	{
		finish_with_error(con);
	}

	MYSQL_RES *result = mysql_store_result(con);

	if (result == NULL)
	{
		finish_with_error(con);
	}

	return result;
}

int DataBase::check_login(char * login, char * pwd)
{
	char buf[2048];
	sprintf_s(buf, "SELECT id\
				   FROM student \
				   WHERE sName='%s'\
				   AND sSurname='%s'"
				   , login, pwd);

	MYSQL_RES *result = exec(buf);
	if (mysql_num_rows(result) == 1)
	{
		MYSQL_ROW row = mysql_fetch_row(result);
		int ret = atoi(row[0]);
		mysql_free_result(result);
		return ret;
	}

	else
	{
		mysql_free_result(result);
		return -1;
	}
		
}
