/*
 * p2p_node.cpp
 *
 *  Created on: 2016-5-31
 *      Author: jay
 */
#include "p2p_node.h"
#include "p2p_msg.h"
#include <memory.h>
#include <string.h>
#include <stdio.h>
extern P2pSendQueue SQueue;

P2pNode::P2pNode(const char *id, struct sockaddr_in nodeinfo)
{
	memcpy(node_id, id, 32);
	memcpy(&node_info, &nodeinfo, sizeof(nodeinfo));
	lifecycle = 5;
	sendtimes = -1;
}

void P2pNode::ResetLife()
{
	 time(&lifecycle);
}

double P2pNode::GetLife()
{
	time_t now;
	time(&now);
	return difftime(now, lifecycle);
}

int P2pNode::GetAddrInfo(_out_ char *addr, _out_ int &port)
{
	if(addr == NULL)
		return -1;
	sprintf(addr, "%s", inet_ntoa(node_info.sin_addr));
	port = node_info.sin_port;
	return 0;
}

int P2pNode::GetNodeId(_out_ char *id)
{
	if(id == NULL)
		return -1;
	memcpy(id, node_id, 32);
	return 0;
} 

int P2pNode::RequestSend(const char *data, int len)
{
	sendtimes = 0;
	memset(senddata, 0, 8096);
	memcpy(senddata, data, len);
	sendlen = len;
	SQueue.SendMsg(*this);
	return len;
}

int P2pNode::RealSend(int sock)
{
	int n = sendto(sock, senddata, sendlen, 0, (struct sockaddr *)&node_info, sizeof(node_info));
	sendtimes++;
	return n;
}
