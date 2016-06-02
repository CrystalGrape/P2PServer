/*
 * p2p_server.cpp
 *
 *  Created on: 2016-5-31
 *      Author: jay
 */
#include "p2p_server.h"
#include "memory.h"
using namespace P2pServer;

P2pParse::P2pParse(const char *recvdata)
{
	try{
		reader.parse(recvdata, root);
	}
	catch(...){
		throw P2P_ERR_PKGWRONG;
	}
}

Value P2pParse::GetJsonRoot()
{
	return root;
}

int P2pUdpServer::ServerInit(int port)
{
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if ( (server = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		return -1;
	if (bind(server, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		return -2;
	return 0;
}

int P2pUdpServer::Listen()
{	
	int len = sizeof(caddr);
	memset(recvdata, 0, 8096);
	recvlen = recvfrom(server, recvdata, 8096, 0, (struct sockaddr*)&caddr, (socklen_t *)&len);
	/*发送模板*/
	//int n = sendto(sock, data, strlen(data), 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
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

P2pMsg::P2pMsg(struct sockaddr_in addr, const char* data, int len)
{
	memcpy(&caddr, &addr, sizeof(caddr));
	recvlen = len;
	memcpy(recvdata, data, 8096);
}

P2pParse P2pMsg::GetParse()
{
	if (recvlen <= 0)
		throw P2P_ERR_PKGWRONG;
	P2pParse parse(recvdata);
	return parse;
}

P2pNode P2pMsg::GetNode(P2pParse parse)
{
	try{
		P2pNode node(parse.GetJsonRoot()["head"]["srcid"].asCString(), caddr);
		return node;
	}catch(...){
		throw P2P_ERR_PKGWRONG;
	}
}




