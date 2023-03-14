#include "work_dir.h"
#include "Facade.h"
#include "PkgProcess.h"
#include "ScriptOp.h"
#include "Pack.h"
#include "localserverlog.h"

#define MAX_OP_BUF_SIZE (1024 * 1024)

IFacadeBusiness *g_poFacadeBusiness = CCGGameFacade::GetInstance();

//初始化收发包库中需要用到的各对象
//用于告知平台具体的收发包所使用的类
int CCGGameFacade::Initialize(IFacadePlatform *poFacadePlatform)
{
	//平台初始化，无需修改
    int nRet = CFacadeBusiness::Initialize(poFacadePlatform);
    if(nRet < 0)
    {
        LOGERR("CFacadeBusiness::Initialize fail, rtnvalue:%d", nRet);
        assert(false);
        return -1;
    }
	//Pack打解包类初始化
    GamePack *pGamePack = new GamePack;
    if (NULL == pGamePack)
    {
        LOGERR("New CG4GamePack fail!");
        assert(false);
        return -2;
    }
	//Process收包处理类初始化
    CG4GameProcess *poGameTPkgProcess = new CG4GameProcess;
    if (NULL == poGameTPkgProcess)
    {
        LOGERR("New CG4GameProcess fail!");
        assert(false);
        return -3;
    }
	//ScriptOp发包处理类初始化
    CG4GameScriptOp *poGameScriptOp = new CG4GameScriptOp;
    if (NULL == poGameScriptOp)
    {
        LOGERR("New CG4GameScriptOp fail!");
        assert(false);
        return -4;
    }
	//将类对象传入平台
    nRet = InitModules(poGameTPkgProcess, poGameScriptOp, NULL, pGamePack, NULL);
    if (nRet < 0)
    {
        assert(false);
        LOGERR("CFacadeBusiness::InitModules fail, rtnvalue:%d", nRet);
        return -5;
    }

    return nRet;
}

