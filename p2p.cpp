/*
/*
 * p2p_node.cpp
 *
 *  Created on: 2016-5-31
 *      Author: jay
 
 
                   _ooOoo_
                  o8888888o
                  88" . "88
                  (| -_- |)
                  O\  =  /O
               ____/`---'\____
             .'  \\|     |//  `.
            /  \\|||  :  |||//  \
           /  _||||| -:- |||||-  \
           |   | \\\  -  /// |   |
           | \_|  ''\---/''  |   |
           \  .-\__  `-`  ___/-. /
         ___`. .'  /--.--\  `. . __
      ."" '<  `.___\_<|>_/___.'  >'"".
     | | :  `- \`.;`\ _ /`;.`/ - ` : | |
     \  \ `-.   \_ __\ /__ _/   .-` /  /
======`-.____`-.___\_____/___.-`____.-'======
                   `=---='
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
         佛祖保佑       永无BUG
*/

#include "p2p_server.h"
#include <iostream>
using namespace std;
using namespace P2pServer;

int main()
{
	P2pUdpServer p2pServer;
	p2pServer.ServerInit(8000);
	char ip[20];
	int port;
	while(1){
		try{
			p2pServer.Listen();
      P2pMsg msg = p2pServer.GetMsg();
			//P2pParse parse = p2pServer.GetParse();
			//这里判断数据包类型，如果是登录包，在这里处理，否则放入队列
			//P2pNode node = p2pServer.GetNode(parse);
			//node.GetAddrInfo(ip, port);
			//cout<<"IPAddress:"<<ip<<"["<<port<<"]"<<endl;
		}catch(int err){
			cout<<"error code:"<<err<<endl;
		}
	}
}
