/*
 * p2p_server.h
 *
 *  Created on: 2016-5-31
 *      Author: jay
 */
#ifndef p2p_server_h
#define p2p_server_h
#include "p2p.h"
#include "p2p_msg.h"

class P2pUdpServer
{
public:
	//服务器初始化
	int ServerInit(int port);
	//监听端口
	int Listen();
	//生成消息类
	P2pMsg GetMsg();
private:
	int server;
	struct sockaddr_in addr;
	struct sockaddr_in caddr;
	int recvlen;
	char recvdata[8096];
	static void *HandleSend(void *arg);
};
#endif
