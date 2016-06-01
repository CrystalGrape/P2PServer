/*
 * p2p_node.cpp
 *
 *  Created on: 2016-5-31
 *      Author: jay
 */
#include "p2p_node.h"
#include <memory.h>
#include <string.h>
#include <stdio.h>
using namespace P2pServer;
P2pNode::P2pNode(const char *id, struct sockaddr_in nodeinfo)
{
	memcpy(node_id, id, 32);
	memcpy(&node_info, &nodeinfo, sizeof(nodeinfo));
	lifecycle = 5;
}

void P2pNode::ResetLife()
{
	lifecycle = 5;
}

void P2pNode::DescLife()
{
	lifecycle--;
}

int P2pNode::GetLife()
{
	return lifecycle;
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
