/*
 * p2p_node.h
 *
 *  Created on: 2016-6-2
 *      Author: jay
 */
#ifndef P2P_H
#define P2P_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
//数据包类型
#define P2P_HEART		0x7001	//心跳包
#define P2P_REQUEST		0x7002	//连接请求包
#define P2P_RST			0x7003	//回复包
#define P2P_STREAM		0x7004	//视频流包
#define P2P_ONLINE		0x7005	//上线请求
//错误类型
#define P2P_ERR_TIMEOUT		0x6001	//超时 
#define P2P_ERR_PKGWRONG	0x6002	//数据包解析错误
#define P2P_ERR_QUEEMPTY	0x6003	//队列为空
#endif