#ifndef _USER_INFO_H_
#define _USER_INFO_H_

#include <string>
#include <vector>
#include <sys/time.h>

#define MAX_BUFF_LEN 1024*1024


class UserInfo
{
public:
	UserInfo(int dwID);
	~UserInfo();
public:
	int dwUin;
	std::string token;

	
};

UserInfo* GetUserInfo(int dwUin);

#endif
