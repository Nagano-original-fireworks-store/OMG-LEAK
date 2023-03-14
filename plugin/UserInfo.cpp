#include "UserInfo.h"
#include <map>

typedef std::map<int, UserInfo*> UserInfoMap;
UserInfoMap gUserInfo;


UserInfo* GetUserInfo(int dwUin)
{
	UserInfoMap::iterator it = gUserInfo.find(dwUin);
	if (it != gUserInfo.end()) {
		return it->second;
	}

	UserInfo* pInfo = new UserInfo(dwUin);
	gUserInfo[dwUin] = pInfo;
	return pInfo;
}


UserInfo::UserInfo( int dwID )
{
	dwUin = dwID;
	token="";
}

UserInfo::~UserInfo()
{

}


