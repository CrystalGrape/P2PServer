/*
 * p2p_server.h
 *
 *  Created on: 2016-5-31
 *      Author: jay
 */
#ifndef p2p_server_h
#define p2p_server_h
#include "p2p_node.h"
#include <json/json.h>
using namespace Json;
//数据包类型
#define P2P_HEART		0x7001	//心跳包
#define P2P_REQUEST		0x7002	//连接请求包
#define P2P_RST			0x7003	//回复包
#define P2P_STREAM		0x7004	//视频流包
#define P2P_ONLINE		0x7005	//上线请求
//错误类型
#define P2P_ERR_TIMEOUT		0x6001	//超时 
#define P2P_ERR_PKGWRONG	0x6002	//数据包解析错误

namespace P2pServer
{
	/*
	*	数据解析类
	*/
	class P2pParse
	{
	public:
		P2pParse(const char *recvdata);
		Value GetJsonRoot();
	private:
		Reader reader;  
		Value root;
	};
	
	class P2pUdpServer
	{
	public:
		//服务器初始化
		int ServerInit(int port);
		//监听端口
		int Listen();
		//获取解析对象
		P2pParse GetParse();
		//获取节点对象
		P2pNode GetNode(P2pParse parse);
	private:
		int server;
		struct sockaddr_in addr;
		struct sockaddr_in caddr;
		int recvlen;
		char recvdata[8096];
	};
}
#endif
