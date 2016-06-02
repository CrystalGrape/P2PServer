/*
 * p2p_server.cpp
 *
 *  Created on: 2016-5-31
 *      Author: jay
 */
#include "p2p_server.h"
#include "memory.h"

P2pSendQueue SQueue;

int P2pUdpServer::ServerInit(int port)
{
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if ( (server = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		return -1;
	if (bind(server, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		return -2;
	pthread_t tid;
	pthread_create(&tid, 0, HandleSend, this);
	return 0;
}

int P2pUdpServer::Listen()
{	
	int len = sizeof(caddr);
	memset(recvdata, 0, 8096);
	recvlen = recvfrom(server, recvdata, 8096, 0, (struct sockaddr*)&caddr, (socklen_t *)&len);

	if (recvlen > 0){
		recvdata[recvlen] = 0;
		return 0;
	}
	return -1;
}


P2pMsg P2pUdpServer::GetMsg()
{
	P2pMsg msg(caddr, recvdata, recvlen);
	return msg;
}

void *P2pUdpServer::HandleSend(void *arg)
{
	P2pUdpServer *server = (P2pUdpServer *)arg;
	while(1)
	{
		P2pNode node = SQueue.RecvMsg();
		node.RealSend(server->server);
	}
}
