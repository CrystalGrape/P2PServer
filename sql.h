/*************************************************************************
    > File Name: sql.h
    > Author: ma6174
    > Mail: 2424994234@qq.com
    > Created Time: 2015年04月14日 星期二 21时12分36秒
 ************************************************************************/
#ifndef _SQL_H_
#define _SQL_H_
#include <iostream>
#include <string.h>
#include <mysql/mysql.h>

class sqlclt
{
	public:
		int Connect();
		//写入脚本
		int WriteDB(char *query,int queryLen);
		void DisConnect();
		bool Login(const char *user, const char *pwd);
		int FindBindDevice(char *macaddr, const char *user);
		~sqlclt();
	private:
		char hostip[20];
		char username[20];
		char pwd[20];
		char dbname[20];
		MYSQL mysql;
};
#endif

