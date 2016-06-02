/*
 * p2p_parse.h
 *
 *  Created on: 2016-6-2
 *      Author: jay
 */
#ifndef P2P_PARSE_H
#define P2P_PARSE_H
#include <json/json.h>
#include "p2p.h"
#include "p2p_node.h"
using namespace Json;
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

#endif