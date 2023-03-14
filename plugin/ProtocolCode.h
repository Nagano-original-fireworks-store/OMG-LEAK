#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__


//定义消息类型到MsgID的映射
enum ProtocolID
{
	C2S_INVALID = 0,
	GetPlayerTokenRsp = 102,
	PlayerLoginRsp = 104,

	C2S_TOTAL
};
//崩4消息打解包所用到的常量
const unsigned short const_head_magic = 0x4567;
const unsigned short const_tail_magic = 0x89AB;




#endif
