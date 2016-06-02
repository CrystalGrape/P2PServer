/*
 * p2p_msg.h
 *
 *  Created on: 2016-6-2
 *      Author: jay
 */
#ifndef P2P_MSG_H
#define P2P_MSG_H
#include <iostream>
#include <queue>
#include <semaphore.h>
#include <pthread.h>
#include "p2p.h"
#include "p2p_msgnode.h"
using namespace std;

typedef queue<P2pMsg> MsgQueue;
typedef queue<P2pNode> SendQueue;
//消息队列
class P2pMsgQueue
{
public:
	P2pMsgQueue();
	int SendMsg(P2pMsg msg);
	P2pMsg RecvMsg();
private:
	MsgQueue qlist;
	sem_t qlist_count;	
};

//发送队列
class P2pSendQueue
{
public:
	P2pSendQueue();
	int SendMsg(P2pNode node);
	P2pNode RecvMsg();
private:
	SendQueue qlist;
	sem_t qlist_count;	
};
#endif