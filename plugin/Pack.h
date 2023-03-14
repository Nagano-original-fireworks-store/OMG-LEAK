#ifndef _Game_PACK_H_
#define _Game_PACK_H_

#include "pack_i.h"

class IFacadePlatform;

#define MAX_BUFF_LEN 1024*1024

/*打解包公共处理类，主要实现以下功能：
PackMsg打包函数：
1. 实现打包PackMsg函数，主要功能是将ScriptOp传入的待打包buffer pItemsToPack 打包到 pPackPkg buffer中
2. 返回待发送的包长度
UnpackMsg解包函数：
1.将待解包的buffer pItemsToPack解包到pUnpackPkg中，并返回解包后的长度
2.该pUnpackPkg和返回的解包长度会传到PkgProcess模块进行后续处理
*/

class GamePack: public IPack
{
public:
	GamePack();
	/*
	描述：打包消息公共处理函数
	参数说明；
	[IN] dwPlayerID: 发包的机器人ID
	[IN] dwMsgID: 待发送包的msgID
	[IN] pItemsToPack: 待打包的缓冲区
	[IN] nItemLen: 待打包的包长度
	[OUT] pPackPkg: 打包后的缓冲区
	[OUT] PkgBufLen: 打包后包长度
	[OUT] nErrorCode: 错误码
	*/
   	virtual int PackMsg(unsigned int dwPlayerID, unsigned int dwMsgID, void *pItemsToPack, int nItemLen, char *pPackPkg, int PkgBufLen, int &nErrorCode);

	/*
	描述：解包公共处理函数
	参数说明；
	[IN] dwPlayerID: 发包的机器人ID
	[IN] pItemsToPack: 待解包的缓冲区
	[IN] nItemLen: 待解包的包长度
	[OUT] pUnpackPkg: 解包后的缓冲区
	[OUT] nErrorCode: 错误码
	[RTN] 解包后的包长度
	*/
    virtual int UnpackMsg(unsigned int dwPlayerID,void *pItemsToPack, int nItemLen, void* &pUnpackPkg, int &nErrorCode);

	//以下三个成员函数平台用，无需关心，按示例实现即可
	virtual int SetHandles(IFacadePlatform *poFacadePlatform);
    virtual int GetRecvMsgFlag();
    virtual unsigned int GetUnpackProtocalID(char *pPkgHeader);

    IFacadePlatform *m_poFacadePlatform;
    char m_pkgbuff[MAX_BUFF_LEN];
	
};

#endif
