#ifndef _Game_PACKET_H_
#define _Game_PACKET_H_
//#include "packet_head.pb.h"
//#include "player.pb.h"
#include "Hk4eProto.h"
#include <google/protobuf/service.h>
#include <cstdint>

#define MAX_ERR_LEN 256

//崩4打解包辅助类，可从崩4服务器代码中提炼出，或与服务器程序沟通了解协议格式后自行实现
class Packet
{
public:
	unsigned short cmd_id_;           // 协议ID
	proto::PacketHead head_;    // head字段
	std::string proto_str_;     // 具体协议数据
	char lastErr[MAX_ERR_LEN];
public:
	//打包函数
	int serializeToString(std::string& str);
	int serializeToArray(char* buf, unsigned int buf_len) const;
	//获取包长度
	uint32_t getPacketLen() const;
	//解包函数
	int32_t parseFromString(const std::string& str);
	int32_t parseFromArray(const char* buf, uint32_t buf_len);
	
	//返回数据包最小长度
	static uint32_t getMinPacketLen();

public:
		static const uint16_t const_head_magic; // 头部魔数
		static const uint16_t const_tail_magic; // 尾部魔数


};

#endif


