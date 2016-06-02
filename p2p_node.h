/*
 * p2p_node.h
 *
 *  Created on: 2016-5-31
 *      Author: jay
 */
#ifndef P2P_NODE_H
#define P2P_NODE_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define _out_
namespace P2pServer
{
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
		//获取地址信息 xxx.xxx.xxx.xxx[xxxx]
		int GetAddrInfo(_out_ char *addr, _out_ int &port);
		//获取节点地址
		int GetNodeId(_out_ char *id);
	private:
		char node_id[32];
		struct sockaddr_in node_info;
		int lifecycle;
	};
}
#endif
