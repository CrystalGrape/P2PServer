/*
 * p2p_node.h
 *
 *  Created on: 2016-5-31
 *      Author: jay
 */
#ifndef P2P_NODE_H
#define P2P_NODE_H
#include "p2p.h"
#define _out_

class P2pNode
{
public:
	P2pNode(const char *id, struct sockaddr_in nodeinfo);
	//重置生命周期
	void ResetLife();
	//减少生命周期
	void DescLife();
	//获取生命周期
	int GetLife();
	//获取地址信息
	int GetAddrInfo(_out_ char *addr, _out_ int &port);
	//获取节点地址
	int GetNodeId(_out_ char *id);
	//请求发送数据
	int RequestSend(const char *data, int len);
	//真正发送数据
	int RealSend(int sock);
	//重置发送次数
	void ResetSendTimes()
	{
		sendtimes = -1;
	}
private:
	char node_id[32];
	struct sockaddr_in node_info;
	int lifecycle;
	char senddata[8096];
	int sendlen;
	int sendtimes;		//重发次数
	/*	-1表示没有有数据需要发送
	*	0表示有数据需要发送
	*	大于0表示发送次数
	*/
};

#endif
