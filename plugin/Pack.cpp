#include <assert.h>
#include "Pack.h"
#include "facadeplatform_i.h"
#include <stdio.h>
#include <string.h>

#include <arpa/inet.h>  
#include "ProtocolCode.h"
//#include "packet_head.pb.h"
//#include "player.pb.h"
#include "Hk4eProto.h"

GamePack::GamePack()
{

}

int GamePack::PackMsg( unsigned int dwPlayerID, unsigned int dwMsgID, void *pItemsToPack, int nItemLen, char *pPackPkg, int PkgBufLen, int &nErrorCode )
{ 

	memcpy(pPackPkg,pItemsToPack,nItemLen);

	
    return nItemLen;
	
}

int GamePack::UnpackMsg(unsigned int dwPlayerID,void *pItemsToPack, int nItemLen, void* &pUnpackPkg, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwPlayerID," nItemLen: %d",nItemLen);

	memcpy(m_pkgbuff,(char *)pItemsToPack, nItemLen);
    pUnpackPkg = m_pkgbuff;
	
    return nItemLen;

}
//固定即可
int GamePack::SetHandles( IFacadePlatform *poFacadePlatform )
{
    m_poFacadePlatform = poFacadePlatform;
    return 0;
}

int GamePack::GetRecvMsgFlag()
{
	m_poFacadePlatform->TestLog(1," GetRecvMsgFlag");

    return 1;
}

unsigned int GamePack::GetUnpackProtocalID( char *pPkgHeader )
{
	m_poFacadePlatform->TestLog(1," GetUnpackProtocalID");

    return 1;
}

