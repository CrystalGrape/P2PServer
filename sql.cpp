/*************************************************************************
    > File Name: sql.cpp
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2015年04月14日 星期二 21时11分40秒
 ************************************************************************/

#include "sql.h"
#include <stdio.h>
#include <string.h>
int sqlclt::Connect()
{
	mysql_init(&mysql);
	strcpy(hostip,"localhost");
	strcpy(username,"root");
	strcpy(pwd,"1234567");
	strcpy(dbname,"gfdb");
	if(!mysql_real_connect(&mysql,hostip,username,pwd,dbname,0,NULL,0))
	{
		return 1;
	}
	else 
		return 0;
}
int sqlclt::WriteDB(char *query,int queryLen)
{
	int flag;
	try{
		flag=mysql_real_query(&mysql,query,queryLen);
	}
	catch(...){
	}
	return flag;
}

bool sqlclt::Login(const char *user, const char *pwd)
{
	MYSQL_RES *res;
	char query[500];
	bool ret = true;
	sprintf(query, "select * from userinfo where userid='%s' and password='%s'",user,pwd);
	int flag=mysql_real_query(&mysql,query,strlen(query));
	res = mysql_store_result(&mysql);
	if(mysql_num_rows(res) == 0)
		ret=false;
	mysql_free_result(res);
	return ret;
}

void sqlclt::DisConnect()
{
	mysql_close(&mysql);
}

sqlclt::~sqlclt()
{
	mysql_close(&mysql);
}

int sqlclt::FindBindDevice(char *macaddr, const char *user)
{
	MYSQL_RES *res;
	char query[500];
	bool ret = true;
	sprintf(query, "select macaddr from bindinfo where userid='%s'",user);
	int flag=mysql_real_query(&mysql,query,strlen(query));
	res = mysql_store_result(&mysql);
	if(mysql_num_rows(res) == 0){
		mysql_free_result(res);
		return -1;
	}
	MYSQL_ROW row=mysql_fetch_row(res);
	for(int t=0;t<mysql_num_fields(res);t++)
	{
		strcpy(macaddr, row[t]);
	}
	mysql_free_result(res);
	return ret;
}
