#include "p2p_parse.h"
P2pParse::P2pParse(const char *recvdata)
{
	try{
		reader.parse(recvdata, root);
	}
	catch(...){
		throw P2P_ERR_PKGWRONG;
	}
}

Value P2pParse::GetJsonRoot()
{
	return root;
}