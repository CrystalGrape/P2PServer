#include "p2p_msg.h"
#include <memory.h>
//P2pMsg
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

//P2pMsgQueue
P2pMsgQueue::P2pMsgQueue()
{
	sem_init(&qlist_count,0,0);  //初始化信号灯为0
}

int P2pMsgQueue::SendMsg(P2pMsg msg)
{
	qlist.push(msg);
	sem_post(&qlist_count);
	return qlist.size();
}

P2pMsg P2pMsgQueue::RecvMsg()
{
	//队列不为空才能进入
	sem_wait(&qlist_count);
	P2pMsg msg = qlist.front();
	qlist.pop();
	return msg;
}

//P2pSendQueue
P2pSendQueue::P2pSendQueue()
{
	sem_init(&qlist_count,0,0);  //初始化信号灯为0
}

int P2pSendQueue::SendMsg(P2pNode node)
{
	qlist.push(node);
	sem_post(&qlist_count);
	return qlist.size();
}

P2pNode P2pSendQueue::RecvMsg()
{
	//队列不为空才能进入
	sem_wait(&qlist_count);
	P2pNode node = qlist.front();
	qlist.pop();
	return node;
}
