#include "p2p_nodemap.h"

int UserMgr::Insert(P2pNode node)
{
	char id[32];
	node.GetNodeId(id);
	um.insert(std::pair<IdKey,P2pNode>(id, node));
	return 1;
}

P2pNode &UserMgr::Read(IdKey key)
{
	User usr = um.find(key);
	return usr->second;
}

int UserMgr::Delete(IdKey key)
{
	User usr = um.find(key);
	um.erase(usr);
	return 1;
}

bool UserMgr::Exist(IdKey key)
{
	User usr = um.find(key);
	if(usr == um.end())
		return false;
	return true;
}

