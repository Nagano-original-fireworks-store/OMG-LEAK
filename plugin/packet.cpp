#include <cstdint>
#include <google/protobuf/service.h>

#include "packet.h"

//#include "packet_head.pb.h"
//#include "player.pb.h"
#include "Hk4eProto.h"
#include <netinet/in.h>
#include "localserverlog.h"


extern int CLocalServerLog::ms_iLogDynamicFlag;




const uint16_t Packet::const_head_magic = 0x4567;
const uint16_t Packet::const_tail_magic = 0x89AB;

//打包
int32_t Packet::serializeToString(std::string& str) {
	uint32_t packet_len = getPacketLen();
	str.resize(packet_len);
	char* buf = const_cast<char*>(str.c_str());
	return serializeToArray(buf, packet_len);
}

int32_t Packet::serializeToArray(char* buf, unsigned int buf_len) const {
	// 空指针校验
	if (nullptr == buf)
	{
	   LOGERR("buf is nullptr");
	   return -1;
	}

	// buf长度校验
	uint32_t packet_len = getPacketLen();
	if (packet_len > buf_len)
	{
	   LOGERR("buf_len=%u is too short, while packet_len=%u", buf_len, packet_len);
	   return -1;
	}

	// 开始序列化
	char* cur_addr = buf;

	// 头部魔数
	uint16_t n_head_magic = htons(Packet::const_head_magic);
	memcpy(cur_addr, &n_head_magic, sizeof(n_head_magic));
	cur_addr += sizeof(n_head_magic);

	// cmd_id
	uint16_t n_cmd_id = htons(cmd_id_);
	memcpy(cur_addr, &n_cmd_id, sizeof(n_cmd_id));
	cur_addr += sizeof(n_cmd_id);

	// head_len
	uint16_t head_len = head_.ByteSize();
	uint16_t n_head_len = htons(head_len);
	memcpy(cur_addr, &n_head_len, sizeof(n_head_len));
	cur_addr += sizeof(n_head_len);

	// body_len
	uint32_t body_len = (uint32_t)proto_str_.length();
	uint32_t n_body_len = htonl(body_len);
	memcpy(cur_addr, &n_body_len, sizeof(n_body_len));
	cur_addr += sizeof(n_body_len);

	// head
	if (0 != head_len)
	{
		if (!head_.SerializeToArray(cur_addr, head_len))
		{
	    	LOGERR("head_.SerializeToArray failed");
			return -1;
		}
		cur_addr += head_len;
	}

	// body: 0的主机、网络字节序一致，所以可以这么判断
	if (0 != body_len)
	{
	   memcpy(cur_addr, proto_str_.c_str(), proto_str_.length());
	   cur_addr += proto_str_.length();
	}

	// 尾部魔数
	uint16_t n_tail_magic = htons(Packet::const_tail_magic);
	memcpy(cur_addr, &n_tail_magic, sizeof(n_tail_magic));
	cur_addr += sizeof(n_tail_magic);

	return 0;

}

uint32_t Packet::getPacketLen() const
{
	// 基本长度 + head + body
	return Packet::getMinPacketLen() + head_.ByteSize() + proto_str_.length();
}

uint32_t Packet::getMinPacketLen()
{
	// 空包包含head_magic, cmd_id, head_len, body_len, tail_magic
	return sizeof(uint16_t) * 4 + sizeof(uint32_t);
}

//解包
int32_t Packet::parseFromString(const std::string& str)
{
    return parseFromArray(str.c_str(), str.length());
}

        // 从char*反序列化
int32_t Packet::parseFromArray(const char* buf, uint32_t buf_len)
{
    // 空指针校验
    if (nullptr == buf)
    {
        LOGERR("buf is nullptr");
        return -1;
    }

    // 最小长度校验
    if (buf_len < getMinPacketLen())
    {
        LOGERR("buf_len=%u is too short", buf_len);
        return -1;
    }

    const char* cur_addr = buf;

    // 校验头部魔数
    if (Packet::const_head_magic != ntohs(*((uint16_t*)cur_addr)))
    {
        LOGERR("head magic error");
        return -1;
    }
    cur_addr += sizeof(Packet::const_head_magic);

    // 取cmd_id
    cmd_id_ = ntohs(*((uint16_t*)cur_addr));
    cur_addr += sizeof(cmd_id_);

    uint16_t head_len = 0;
    uint32_t body_len = 0;

    // 取head_len
    head_len = ntohs(*((uint16_t*)cur_addr));
    cur_addr += sizeof(head_len);

    // 取body_len
    body_len = ntohl(*((uint32_t*)cur_addr));
    cur_addr += sizeof(body_len);

    // 校验长度是否足够
    uint32_t packet_len = Packet::getMinPacketLen() + head_len + body_len;
    if (packet_len > buf_len)
    {
        LOGERR("buf_len=%u is too short, packet_len=%u", buf_len, packet_len);
        return -1;
    }


    // 取head
    if (!head_.ParseFromArray(cur_addr, head_len))
    {
        LOGERR("head_.ParseFromArray failed");
        return -1;
    }
    cur_addr += head_len;

    // 取body
    proto_str_.assign(cur_addr, body_len);
    cur_addr += body_len;

    // 校验尾部魔数
    if (Packet::const_tail_magic != ntohs(*((uint16_t*)cur_addr)))
    {
        LOGERR("tail magic error 0x%X", ntohs(*((uint16_t*)cur_addr)));
        return -1;
    }

    return 0;
}


