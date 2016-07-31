/*
 * p2p_handle.cpp
 *
 *  Created on: 2016-6-2
 *      Author: jay
 */
#include "p2p_handle.h"
#include "p2p_node.h"
#include "p2p_nodemap.h"
#include "sql.h"
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
		case P2P_DEVICE:
			OnDevice(msg);
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
	if(mgr->Exist(msg.GetParse().GetJsonRoot()["head"]["srcid"].asCString())){
		mgr->Read(msg.GetParse().GetJsonRoot()["head"]["srcid"].asCString()).ResetLife();
	}
}

void P2pEvent::OnRequest(P2pMsg msg)
{
	FastWriter writer;
	Value head;
	Value playload;
	Value pkg;
	head["pkgtype"] = P2P_RST;
	head["srcid"] = "000000";
	head["sendtime"] = 0;
	P2pNode node = msg.GetNode(msg.GetParse());
	
	UserMgr *mgr = UserMgr::GetInstance();
	if(mgr->Exist(msg.GetParse().GetJsonRoot()["head"]["srcid"].asCString())){
		//从数据库中找到绑定用户
		sqlclt sc;
		sc.Connect();
		char macaddr[32];
		sc.FindBindDevice(macaddr, msg.GetParse().GetJsonRoot()["head"]["srcid"].asCString());
		if(mgr->Exist(macaddr)){
			head["index"] = 1;
			char addr[30];
			int port;
			cout<<mgr->Read(macaddr).GetLife()<<endl;
			if(mgr->Read(macaddr).GetLife() <= 5){
				mgr->Read(macaddr).GetAddrInfo(addr, port);
				playload["destip"] = addr;
				playload["desport"] = port;
				pkg["head"] = head;
				pkg["playload"] = playload;
				string json_str=writer.write(pkg);
				node.RequestSend(json_str.c_str(),json_str.size());
			}else{
				head["index"] = 0;
				playload["errcode"] = P2P_ERR_NODEST;
				pkg["head"] = head;
				pkg["playload"] = playload;
				string json_str=writer.write(pkg);
				cout<<json_str.c_str();
				node.RequestSend(json_str.c_str(),json_str.size());
			}
		}else{
			head["index"] = 0;
			playload["errcode"] = P2P_ERR_NODEST;
			pkg["head"] = head;
			pkg["playload"] = playload;
			string json_str=writer.write(pkg);
			cout<<json_str.c_str();
			node.RequestSend(json_str.c_str(),json_str.size());
		}
	}else{
		//无效登录
		head["index"] = 0;
		playload["errcode"] = P2P_ERR_LOGOUT;
		pkg["head"] = head;
		pkg["playload"] = playload;
		string json_str=writer.write(pkg);
		node.RequestSend(json_str.c_str(),json_str.size());
	}
}

void P2pEvent::OnRst(P2pMsg msg)
{
	
}

void P2pEvent::OnOnline(P2pMsg msg)
{
	P2pNode node = msg.GetNode(msg.GetParse());
	sqlclt sc;
	sc.Connect();
	Value root=msg.GetParse().GetJsonRoot();
	
	FastWriter writer;
	Value head;
	Value playload;
	Value pkg;
	head["pkgtype"] = P2P_RST;
	head["srcid"] = "000000";
	head["sendtime"] = 0;
	if(sc.Login(root["playload"]["id"].asCString(),root["playload"]["password"].asCString())){
		//设置生命周期
		head["index"] = 1;
		node.ResetLife();
		UserMgr *mgr = UserMgr::GetInstance();
		if(mgr->Exist(msg.GetParse().GetJsonRoot()["head"]["srcid"].asCString())){
			mgr->Delete(msg.GetParse().GetJsonRoot()["head"]["srcid"].asCString());
		}
		mgr->Insert(node);
		pkg["head"] = head;
		pkg["playload"] = playload;
		string json_str=writer.write(pkg);
		node.RequestSend(json_str.c_str(),json_str.size());
		printf("login success\n");
	}else{
		//验证失败
		head["index"] = 0;
		pkg["head"] = head;
		pkg["playload"] = playload;
		string json_str=writer.write(pkg);
		node.RequestSend(json_str.c_str(),json_str.size());
		printf("login failed\n");
	}
}

void P2pEvent::OnDevice(P2pMsg msg)
{
	UserMgr *mgr = UserMgr::GetInstance();
	P2pNode node = msg.GetNode(msg.GetParse());
	if(mgr->Exist(msg.GetParse().GetJsonRoot()["head"]["srcid"].asCString())){
		mgr->Delete(msg.GetParse().GetJsonRoot()["head"]["srcid"].asCString());
	}
	node.ResetLife();
	mgr->Insert(node);
}
