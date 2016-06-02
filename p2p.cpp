/*
/*
 * p2p_node.cpp
 *
 *  Created on: 2016-5-31
 *      Author: jay
 
 
                   _ooOoo_
                  o8888888o
                  88" . "88
                  (| -_- |)
                  O\  =  /O
               ____/`---'\____
             .'  \\|     |//  `.
            /  \\|||  :  |||//  \
           /  _||||| -:- |||||-  \
           |   | \\\  -  /// |   |
           | \_|  ''\---/''  |   |
           \  .-\__  `-`  ___/-. /
         ___`. .'  /--.--\  `. . __
      ."" '<  `.___\_<|>_/___.'  >'"".
     | | :  `- \`.;`\ _ /`;.`/ - ` : | |
     \  \ `-.   \_ __\ /__ _/   .-` /  /
======`-.____`-.___\_____/___.-`____.-'======
                   `=---='
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
         佛祖保佑       永无BUG
*/

#include "p2p.h"
#include <iostream>
using namespace std;
#include "p2p_msg.h"
#include "p2p_handle.h"
#include "p2p_server.h"
int main()
{
  P2pMsgQueue ql;
	P2pUdpServer p2pServer;
	p2pServer.ServerInit(8000);
  P2pHandle handle(&ql);
	while(1){
		try{
			p2pServer.Listen();
      P2pMsg msg = p2pServer.GetMsg();
      ql.SendMsg(msg);
		}catch(int err){
			cout<<"error code:"<<err<<endl;
		}
	}
}
