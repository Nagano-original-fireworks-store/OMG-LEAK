#ifndef _GAME_FACADE_H__
#define _GAME_FACADE_H__

#include "facadebusiness.h"
#include "tsingleton.h"


//平台初始化类，格式固定，仅实现一个Initialize接口即可
class CCGGameFacade:public CFacadeBusiness,
                    public TSingleton<CCGGameFacade>
{
    DECLARE_SINGLETON_CLASS(CCGGameFacade)

public:
	
    virtual int Initialize( IFacadePlatform *poFacadePlatform );

};

#endif

