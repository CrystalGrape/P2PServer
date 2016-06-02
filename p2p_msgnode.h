#pragma once
#include "p2p_parse.h"

/*
*	消息类
*/
class P2pMsg
{
public:
	P2pMsg(struct sockaddr_in addr, const char *data, int len);
	//获取解析对象
	P2pParse GetParse();
	//获取节点对象
	P2pNode GetNode(P2pParse parse);
private:
	struct sockaddr_in caddr;
	int recvlen;
	char recvdata[8096];
};