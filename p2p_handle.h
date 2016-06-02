/*
 * p2p_handle.h
 *
 *  Created on: 2016-6-2
 *      Author: jay
 */
#ifndef P2P_HANDLE_H
#define P2P_HANDLE_H
#include <pthread.h>
#include <json/json.h>
#include "p2p.h"
#include "p2p_msg.h"
using namespace Json;

class P2pEvent
{
public:
	void CallEvent(Value root, P2pMsg msg);
private:
	/*心跳包处理*/
	void OnHeart(P2pMsg msg);
	/*连接请求包处理*/
	void OnRequest(P2pMsg msg);
	/*回复包处理*/
	void OnRst(P2pMsg msg);
	/*上线包处理*/
	void OnOnline(P2pMsg msg);
	Value pkg;
};

class P2pHandle
{
public:
	P2pHandle(P2pMsgQueue *ql);
private:
	P2pMsgQueue *qlist;
	//数据处理线程
	static void *HandleThread(void *arg);
};

#endif
