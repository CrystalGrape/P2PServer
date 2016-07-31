/*
 * p2p_handle.cpp
 *
 *  Created on: 2016-6-2
 *      Author: jay
 */
#include "p2p_handle.h"
#include "p2p_node.h"
#include "p2p_nodemap.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

P2pHandle::P2pHandle(P2pMsgQueue *ql)
{
	qlist = ql;
	pthread_t tid;
	pthread_create(&tid, 0, HandleThread, this);
}

void *P2pHandle::HandleThread(void *arg)
{
	P2pHandle *handle = (P2pHandle *)arg;

	while(1)
	{
		try
		{
			P2pMsg msg = handle->qlist->RecvMsg();
			P2pParse parse = msg.GetParse();
			P2pEvent event;
			event.CallEvent(parse.GetJsonRoot(), msg);
		}
		catch(int err)
		{
			switch(err)
			{
				case P2P_ERR_TIMEOUT:
					break;
				case P2P_ERR_PKGWRONG:
					break;
				case P2P_ERR_QUEEMPTY:
					break;
				default:
					break;
			}
		}
	}
}

void P2pEvent::CallEvent(Value root, P2pMsg msg)
{
	try{
		pkg = root;
		switch(root["head"]["pkgtype"].asInt())
		{
		case P2P_HEART:
			OnHeart(msg);
			break;
		case P2P_REQUEST:
			OnRequest(msg);
			break;
		case P2P_RST:
			OnRst(msg);
			break;
		case P2P_ONLINE:
			OnOnline(msg);
			break;
		default:
			break;
		}
	}
	catch(...)
	{
		throw P2P_ERR_PKGWRONG;
	}
}

void P2pEvent::OnHeart(P2pMsg msg)
{
	//重置生命周期
	UserMgr *mgr = UserMgr::GetInstance();
	mgr->Read(msg.GetParse().GetJsonRoot()["head"]["srcid"].asCString()).ResetLife();
}

void P2pEvent::OnRequest(P2pMsg msg)
{
	UserMgr *mgr = UserMgr::GetInstance();
	printf("%lf\n",mgr->Read(msg.GetParse().GetJsonRoot()["head"]["srcid"].asCString()).GetLife());
}

void P2pEvent::OnRst(P2pMsg msg)
{

}

void P2pEvent::OnOnline(P2pMsg msg)
{
	//设置生命周期
	P2pNode node = msg.GetNode(msg.GetParse());
	node.ResetLife();
	UserMgr *mgr = UserMgr::GetInstance();
	mgr->Insert(node);
}
