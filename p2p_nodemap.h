#ifndef p2p_nodemap_h
#define p2p_nodemap_h
#include <map>
#include <iostream>
#include <memory.h>
#include <string.h>
#include "p2p_node.h"
class IdKey
{
public:
	IdKey(const char *id)
	{
		memcpy(this->id, id, 32);
	}
	friend bool operator<(const IdKey &a, const IdKey &b)
	{
		return (strcmp(a.id,b.id) < 0)?true:false;
	}
private:
	char id[32];
};

typedef std::map<IdKey,P2pNode> UserMap;
typedef std::map<IdKey,P2pNode>::iterator User;

class UserMgr
{
public:
	static UserMgr *GetInstance()
	{
		static UserMgr *instance=new UserMgr();
		return instance;
	}
	int Insert(P2pNode node);
	P2pNode &Read(IdKey key);
	int Delete(IdKey key);
private:
	UserMgr(){};
	UserMgr(const UserMgr &um){};
	UserMgr &operator=(const UserMgr &um){};
	UserMap um;
};
#endif
