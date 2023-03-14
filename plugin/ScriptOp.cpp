#include <stdio.h>
//#include <direct.h>
#include "ScriptOp.h"
#include "facadeplatform_i.h"
#include "Pack.h"
#include "ProtocolCode.h"
#include <google/protobuf/service.h>
//#include "packet_head.pb.h"
//#include "player.pb.h"
#include "Hk4eProto.h"

#include "UserInfo.h"
#include <time.h>
#include <stdlib.h>

#include <string> 
#include <fstream>  
#include <sys/time.h>
#include <math.h>
#include "packet.h"

#include <google/protobuf/util/json_util.h>

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>


using namespace std;

//no need to auto create
CG4GameScriptOp::CG4GameScriptOp()
{
	//初始化发包函数映射表
	init(m_mapDealScriptOp);
	//初始化各种自定义变量
	option.add_whitespace=true;
	option.preserve_proto_field_names=true;
	option.always_print_primitive_fields=true;
	
}

CG4GameScriptOp::~CG4GameScriptOp()
{
	//可留空
}

/*
发送消息体公用函数
参数说明
[IN] dwUin: 机器人编号
[IN] iMsgID: 消息唯一识别ID
[IN] pParam: 平台参数
[IN] nPkgBufLen: 待发送包长度

[依赖项] this->m_pOpBuf: 待发送的包内容buffer
[依赖项] pParam->m_pPkgBuf: 最终发包的buffer
[依赖项] pParam->m_nBufLen: 最终发包长度

[RTN] =0: 发包成功
<0: 发包失败
*/
int CG4GameScriptOp::SendPkg(unsigned int dwUin, int iMsgID, STScriptOpParam *pParam, int nPkgBufLen)
{
	if (iMsgID == -1)
		return 0;

	//打印日志
	m_poFacadePlatform->TestLog(dwUin, "Send req=%d, pkgsize=%d. (%s:%d)", iMsgID, nPkgBufLen, __FUNCTION__, __LINE__);

	//调用pack.cpp中的PackMsg处理发送消息中的公共部分
	pParam->m_nPackedPkgLen = m_poPack->PackMsg(dwUin, iMsgID, this->m_pOpBuf, nPkgBufLen,
		(char *)pParam->m_pPkgBuf, pParam->m_nBufLen, pParam->m_nErrCode);
	//配置待发送消息ID为消息ID
	pParam->m_nMsgID = (unsigned)iMsgID;

	return 0;
}

//no need to auto create
const char * CG4GameScriptOp::GetCurDateTimeCStr(struct timeval *pstNowTime) {
	struct timeval stLogTv;
    static char sTimeStr[100 + 1] = {0};

    if (!pstNowTime)
    {
        gettimeofday(&stLogTv,NULL);
        pstNowTime = &stLogTv;
    }

	
	static char s[50];
	struct tm curr;
	curr = *localtime(&(pstNowTime->tv_sec));

    snprintf(s, sizeof(s)-1, "%02d:%02d:%02d", curr.tm_hour, curr.tm_min, curr.tm_sec);
	
	
    snprintf(sTimeStr,100,"[%s.%.6ld]",s,(long)pstNowTime->tv_usec);

    return sTimeStr;

}

//no need to auto create
void CG4GameScriptOp::PackProtobuf(unsigned int dwUin, unsigned short wCmdID, google::protobuf::Message &req, string &data_pb)
{
	proto::PacketHead head;//消息头
	string jsonheadstr = GetJsonStr("PacketHead");
	google::protobuf::util::JsonStringToMessage(jsonheadstr, &head);

	//计算消息总长度
	int length = sizeof(unsigned short) * 4 + sizeof(unsigned int);
	length += head.ByteSize();
	//length+=body_string.length();
	//构造消息体buffer长度
	data_pb.resize(length);

	//使用Packet类处理具体打解包
	Packet packet;
	//设置packet中的cmd_id
	packet.cmd_id_ = wCmdID;
	//将消息体序列化到packet中
	req.SerializeToString(&packet.proto_str_);
	//设置包头内容
	packet.head_.set_rpc_id(dwUin);
	//将整个packet序列化到data_pb buffer中
	packet.serializeToString(data_pb);

	//将data_pb buffer拷到平台层待发送的缓冲区this->m_pOpBuf
	memcpy(this->m_pOpBuf, data_pb.c_str(), data_pb.length());
	string debug_str;
	google::protobuf::util::MessageToJsonString(head, &debug_str,option);
	debug_str = "\n<head>\n" + debug_str + "\n</head>";
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
}

string CG4GameScriptOp::GetJsonStr(string filename) {
	//char buffer[MAX_PATH];
	//getcwd(buffer, MAX_PATH);

	//string file = "/home/data/release/cggaps_test/bin/jsonData/" + filename;
	string file = "bin/jsonData/" + filename;
	//string file = buffer;
	//file += "/jsonData/" + filename
	string jsonstr;
	string rs_str = "";

	ifstream infile;
	infile.open(file.data());
	while(getline(infile, jsonstr))
	{
		rs_str += jsonstr;
	}
	infile.close();

	return rs_str;
}

//no need to auto create
int CG4GameScriptOp::DoPlayerLoginReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerLoginReq req;
	string jsonstr = GetJsonStr("PlayerLoginReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	UserInfo *user = GetUserInfo(dwUin);
	req.set_token(user->token);
	
	
	unsigned short wCmdID = proto::PlayerLoginReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerLoginReq\n" + debug_str + "</send>";
		
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

//auto created code start
int CG4GameScriptOp::DoEntityFightPropChangeReasonNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EntityFightPropChangeReasonNotify req;
	string jsonstr = GetJsonStr("EntityFightPropChangeReasonNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EntityFightPropChangeReasonNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EntityFightPropChangeReasonNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerPropNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerPropNotify req;
	string jsonstr = GetJsonStr("PlayerPropNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerPropNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerPropNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoUnfreezeGroupLimitNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::UnfreezeGroupLimitNotify req;
	string jsonstr = GetJsonStr("UnfreezeGroupLimitNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::UnfreezeGroupLimitNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" UnfreezeGroupLimitNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoBeginCameraSceneLookNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::BeginCameraSceneLookNotify req;
	string jsonstr = GetJsonStr("BeginCameraSceneLookNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::BeginCameraSceneLookNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" BeginCameraSceneLookNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarDataNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarDataNotify req;
	string jsonstr = GetJsonStr("AvatarDataNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarDataNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarDataNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoShowMessageNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ShowMessageNotify req;
	string jsonstr = GetJsonStr("ShowMessageNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ShowMessageNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ShowMessageNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarChangeElementTypeReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarChangeElementTypeReq req;
	string jsonstr = GetJsonStr("AvatarChangeElementTypeReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarChangeElementTypeReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarChangeElementTypeReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerLevelRewardUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerLevelRewardUpdateNotify req;
	string jsonstr = GetJsonStr("PlayerLevelRewardUpdateNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerLevelRewardUpdateNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerLevelRewardUpdateNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoBargainTerminateNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::BargainTerminateNotify req;
	string jsonstr = GetJsonStr("BargainTerminateNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::BargainTerminateNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" BargainTerminateNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEvtCreateGadgetNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EvtCreateGadgetNotify req;
	string jsonstr = GetJsonStr("EvtCreateGadgetNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EvtCreateGadgetNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EvtCreateGadgetNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarEquipChangeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarEquipChangeNotify req;
	string jsonstr = GetJsonStr("AvatarEquipChangeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarEquipChangeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarEquipChangeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSetPlayerBirthdayReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SetPlayerBirthdayReq req;
	string jsonstr = GetJsonStr("SetPlayerBirthdayReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SetPlayerBirthdayReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SetPlayerBirthdayReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoForgeStartReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ForgeStartReq req;
	string jsonstr = GetJsonStr("ForgeStartReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ForgeStartReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ForgeStartReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoTowerTeamSelectReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::TowerTeamSelectReq req;
	string jsonstr = GetJsonStr("TowerTeamSelectReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::TowerTeamSelectReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" TowerTeamSelectReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoMaterialDeleteReturnNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::MaterialDeleteReturnNotify req;
	string jsonstr = GetJsonStr("MaterialDeleteReturnNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::MaterialDeleteReturnNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" MaterialDeleteReturnNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneForceLockNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneForceLockNotify req;
	string jsonstr = GetJsonStr("SceneForceLockNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneForceLockNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneForceLockNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSetPlayerSignatureReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SetPlayerSignatureReq req;
	string jsonstr = GetJsonStr("SetPlayerSignatureReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SetPlayerSignatureReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SetPlayerSignatureReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoStoreItemDelNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::StoreItemDelNotify req;
	string jsonstr = GetJsonStr("StoreItemDelNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::StoreItemDelNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" StoreItemDelNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoMarkEntityInMinMapNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::MarkEntityInMinMapNotify req;
	string jsonstr = GetJsonStr("MarkEntityInMinMapNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::MarkEntityInMinMapNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" MarkEntityInMinMapNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoTakeBattlePassMissionPointReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::TakeBattlePassMissionPointReq req;
	string jsonstr = GetJsonStr("TakeBattlePassMissionPointReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::TakeBattlePassMissionPointReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" TakeBattlePassMissionPointReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEvtBeingHitNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EvtBeingHitNotify req;
	string jsonstr = GetJsonStr("EvtBeingHitNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EvtBeingHitNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EvtBeingHitNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSpringUseReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SpringUseReq req;
	string jsonstr = GetJsonStr("SpringUseReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SpringUseReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SpringUseReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoStoreItemChangeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::StoreItemChangeNotify req;
	string jsonstr = GetJsonStr("StoreItemChangeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::StoreItemChangeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" StoreItemChangeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEntityFightPropUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EntityFightPropUpdateNotify req;
	string jsonstr = GetJsonStr("EntityFightPropUpdateNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EntityFightPropUpdateNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EntityFightPropUpdateNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarPropChangeReasonNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarPropChangeReasonNotify req;
	string jsonstr = GetJsonStr("AvatarPropChangeReasonNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarPropChangeReasonNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarPropChangeReasonNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoTowerFloorRecordChangeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::TowerFloorRecordChangeNotify req;
	string jsonstr = GetJsonStr("TowerFloorRecordChangeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::TowerFloorRecordChangeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" TowerFloorRecordChangeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoElementReactionLogNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ElementReactionLogNotify req;
	string jsonstr = GetJsonStr("ElementReactionLogNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ElementReactionLogNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ElementReactionLogNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDoGachaReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DoGachaReq req;
	string jsonstr = GetJsonStr("DoGachaReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DoGachaReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DoGachaReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEnterWorldFogAreaNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EnterWorldFogAreaNotify req;
	string jsonstr = GetJsonStr("EnterWorldFogAreaNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EnterWorldFogAreaNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EnterWorldFogAreaNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoBargainOfferPriceReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::BargainOfferPriceReq req;
	string jsonstr = GetJsonStr("BargainOfferPriceReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::BargainOfferPriceReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" BargainOfferPriceReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEvtAvatarSitDownNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EvtAvatarSitDownNotify req;
	string jsonstr = GetJsonStr("EvtAvatarSitDownNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EvtAvatarSitDownNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EvtAvatarSitDownNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetPushTipsRewardReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetPushTipsRewardReq req;
	string jsonstr = GetJsonStr("GetPushTipsRewardReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetPushTipsRewardReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetPushTipsRewardReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerLogoutNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerLogoutNotify req;
	string jsonstr = GetJsonStr("PlayerLogoutNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerLogoutNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerLogoutNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlatformStopRouteNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlatformStopRouteNotify req;
	string jsonstr = GetJsonStr("PlatformStopRouteNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlatformStopRouteNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlatformStopRouteNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSetEntityClientDataNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SetEntityClientDataNotify req;
	string jsonstr = GetJsonStr("SetEntityClientDataNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SetEntityClientDataNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SetEntityClientDataNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoWorldOwnerBlossomScheduleInfoNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::WorldOwnerBlossomScheduleInfoNotify req;
	string jsonstr = GetJsonStr("WorldOwnerBlossomScheduleInfoNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::WorldOwnerBlossomScheduleInfoNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" WorldOwnerBlossomScheduleInfoNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoQueryPathReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::QueryPathReq req;
	string jsonstr = GetJsonStr("QueryPathReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::QueryPathReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" QueryPathReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPushTipsAllDataNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PushTipsAllDataNotify req;
	string jsonstr = GetJsonStr("PushTipsAllDataNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PushTipsAllDataNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PushTipsAllDataNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerLogoutReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerLogoutReq req;
	string jsonstr = GetJsonStr("PlayerLogoutReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerLogoutReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerLogoutReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoChallengeRecordNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ChallengeRecordNotify req;
	string jsonstr = GetJsonStr("ChallengeRecordNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ChallengeRecordNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ChallengeRecordNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEnterSceneWeatherAreaNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EnterSceneWeatherAreaNotify req;
	string jsonstr = GetJsonStr("EnterSceneWeatherAreaNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EnterSceneWeatherAreaNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EnterSceneWeatherAreaNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoTakeBattlePassRewardReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::TakeBattlePassRewardReq req;
	string jsonstr = GetJsonStr("TakeBattlePassRewardReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::TakeBattlePassRewardReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" TakeBattlePassRewardReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSetOpenStateReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SetOpenStateReq req;
	string jsonstr = GetJsonStr("SetOpenStateReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SetOpenStateReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SetOpenStateReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonCandidateTeamKickReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonCandidateTeamKickReq req;
	string jsonstr = GetJsonStr("DungeonCandidateTeamKickReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonCandidateTeamKickReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonCandidateTeamKickReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneTransToPointReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneTransToPointReq req;
	string jsonstr = GetJsonStr("SceneTransToPointReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneTransToPointReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneTransToPointReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetDungeonEntryExploreConditionReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetDungeonEntryExploreConditionReq req;
	string jsonstr = GetJsonStr("GetDungeonEntryExploreConditionReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetDungeonEntryExploreConditionReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetDungeonEntryExploreConditionReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoWatcherAllDataNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::WatcherAllDataNotify req;
	string jsonstr = GetJsonStr("WatcherAllDataNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::WatcherAllDataNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" WatcherAllDataNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEvtBulletMoveNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EvtBulletMoveNotify req;
	string jsonstr = GetJsonStr("EvtBulletMoveNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EvtBulletMoveNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EvtBulletMoveNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerInvestigationNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerInvestigationNotify req;
	string jsonstr = GetJsonStr("PlayerInvestigationNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerInvestigationNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerInvestigationNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetPlayerSocialDetailReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetPlayerSocialDetailReq req;
	string jsonstr = GetJsonStr("GetPlayerSocialDetailReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetPlayerSocialDetailReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetPlayerSocialDetailReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonCandidateTeamChangeAvatarReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonCandidateTeamChangeAvatarReq req;
	string jsonstr = GetJsonStr("DungeonCandidateTeamChangeAvatarReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonCandidateTeamChangeAvatarReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonCandidateTeamChangeAvatarReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoItemAddHintNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ItemAddHintNotify req;
	string jsonstr = GetJsonStr("ItemAddHintNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ItemAddHintNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ItemAddHintNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoForgeQueueDataNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ForgeQueueDataNotify req;
	string jsonstr = GetJsonStr("ForgeQueueDataNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ForgeQueueDataNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ForgeQueueDataNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoUnlockWorldFogAreaNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::UnlockWorldFogAreaNotify req;
	string jsonstr = GetJsonStr("UnlockWorldFogAreaNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::UnlockWorldFogAreaNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" UnlockWorldFogAreaNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoLeaveSceneReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::LeaveSceneReq req;
	string jsonstr = GetJsonStr("LeaveSceneReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::LeaveSceneReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" LeaveSceneReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAddRandTaskInfoNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AddRandTaskInfoNotify req;
	string jsonstr = GetJsonStr("AddRandTaskInfoNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AddRandTaskInfoNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AddRandTaskInfoNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarLifeStateChangeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarLifeStateChangeNotify req;
	string jsonstr = GetJsonStr("AvatarLifeStateChangeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarLifeStateChangeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarLifeStateChangeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerSetPauseReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerSetPauseReq req;
	string jsonstr = GetJsonStr("PlayerSetPauseReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerSetPauseReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerSetPauseReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoUnlockTransPointReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::UnlockTransPointReq req;
	string jsonstr = GetJsonStr("UnlockTransPointReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::UnlockTransPointReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" UnlockTransPointReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPathfindingPingNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PathfindingPingNotify req;
	string jsonstr = GetJsonStr("PathfindingPingNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PathfindingPingNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PathfindingPingNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPathfindingEnterSceneReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PathfindingEnterSceneReq req;
	string jsonstr = GetJsonStr("PathfindingEnterSceneReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PathfindingEnterSceneReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PathfindingEnterSceneReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonCandidateTeamCreateReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonCandidateTeamCreateReq req;
	string jsonstr = GetJsonStr("DungeonCandidateTeamCreateReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonCandidateTeamCreateReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonCandidateTeamCreateReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoWorldPlayerReviveReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::WorldPlayerReviveReq req;
	string jsonstr = GetJsonStr("WorldPlayerReviveReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::WorldPlayerReviveReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" WorldPlayerReviveReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarFightPropUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarFightPropUpdateNotify req;
	string jsonstr = GetJsonStr("AvatarFightPropUpdateNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarFightPropUpdateNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarFightPropUpdateNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoLogTalkNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::LogTalkNotify req;
	string jsonstr = GetJsonStr("LogTalkNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::LogTalkNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" LogTalkNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDoSetPlayerBornDataNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DoSetPlayerBornDataNotify req;
	string jsonstr = GetJsonStr("DoSetPlayerBornDataNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DoSetPlayerBornDataNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DoSetPlayerBornDataNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonCandidateTeamPlayerLeaveNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonCandidateTeamPlayerLeaveNotify req;
	string jsonstr = GetJsonStr("DungeonCandidateTeamPlayerLeaveNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonCandidateTeamPlayerLeaveNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonCandidateTeamPlayerLeaveNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlatformChangeRouteNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlatformChangeRouteNotify req;
	string jsonstr = GetJsonStr("PlatformChangeRouteNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlatformChangeRouteNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlatformChangeRouteNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoReliquaryPromoteReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ReliquaryPromoteReq req;
	string jsonstr = GetJsonStr("ReliquaryPromoteReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ReliquaryPromoteReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ReliquaryPromoteReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDailyTaskDataNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DailyTaskDataNotify req;
	string jsonstr = GetJsonStr("DailyTaskDataNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DailyTaskDataNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DailyTaskDataNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEvtSetAttackTargetNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EvtSetAttackTargetNotify req;
	string jsonstr = GetJsonStr("EvtSetAttackTargetNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EvtSetAttackTargetNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EvtSetAttackTargetNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetPlayerTokenReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetPlayerTokenReq req;
	string jsonstr = GetJsonStr("GetPlayerTokenReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetPlayerTokenReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetPlayerTokenReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoHitClientTrivialNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::HitClientTrivialNotify req;
	string jsonstr = GetJsonStr("HitClientTrivialNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::HitClientTrivialNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" HitClientTrivialNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoJoinPlayerSceneReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::JoinPlayerSceneReq req;
	string jsonstr = GetJsonStr("JoinPlayerSceneReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::JoinPlayerSceneReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" JoinPlayerSceneReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGMShowObstacleReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GMShowObstacleReq req;
	string jsonstr = GetJsonStr("GMShowObstacleReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GMShowObstacleReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GMShowObstacleReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarCardChangeReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarCardChangeReq req;
	string jsonstr = GetJsonStr("AvatarCardChangeReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarCardChangeReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarCardChangeReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoChangeGameTimeReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ChangeGameTimeReq req;
	string jsonstr = GetJsonStr("ChangeGameTimeReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ChangeGameTimeReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ChangeGameTimeReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonChallengeFinishNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonChallengeFinishNotify req;
	string jsonstr = GetJsonStr("DungeonChallengeFinishNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonChallengeFinishNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonChallengeFinishNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoQuestProgressUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::QuestProgressUpdateNotify req;
	string jsonstr = GetJsonStr("QuestProgressUpdateNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::QuestProgressUpdateNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" QuestProgressUpdateNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEntityJumpNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EntityJumpNotify req;
	string jsonstr = GetJsonStr("EntityJumpNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EntityJumpNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EntityJumpNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSealBattleProgressNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SealBattleProgressNotify req;
	string jsonstr = GetJsonStr("SealBattleProgressNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SealBattleProgressNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SealBattleProgressNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoJoinPlayerFailNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::JoinPlayerFailNotify req;
	string jsonstr = GetJsonStr("JoinPlayerFailNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::JoinPlayerFailNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" JoinPlayerFailNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoClientScriptEventNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ClientScriptEventNotify req;
	string jsonstr = GetJsonStr("ClientScriptEventNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ClientScriptEventNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ClientScriptEventNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoClientFpsStatusNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ClientFpsStatusNotify req;
	string jsonstr = GetJsonStr("ClientFpsStatusNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ClientFpsStatusNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ClientFpsStatusNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSetSceneWeatherAreaReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SetSceneWeatherAreaReq req;
	string jsonstr = GetJsonStr("SetSceneWeatherAreaReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SetSceneWeatherAreaReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SetSceneWeatherAreaReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetMailItemReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetMailItemReq req;
	string jsonstr = GetJsonStr("GetMailItemReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetMailItemReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetMailItemReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGivingRecordChangeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GivingRecordChangeNotify req;
	string jsonstr = GetJsonStr("GivingRecordChangeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GivingRecordChangeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GivingRecordChangeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoCreateMassiveEntityReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::CreateMassiveEntityReq req;
	string jsonstr = GetJsonStr("CreateMassiveEntityReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::CreateMassiveEntityReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" CreateMassiveEntityReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoClientAbilityInitBeginNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ClientAbilityInitBeginNotify req;
	string jsonstr = GetJsonStr("ClientAbilityInitBeginNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ClientAbilityInitBeginNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ClientAbilityInitBeginNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoBuyGoodsReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::BuyGoodsReq req;
	string jsonstr = GetJsonStr("BuyGoodsReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::BuyGoodsReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" BuyGoodsReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoForgeGetQueueDataReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ForgeGetQueueDataReq req;
	string jsonstr = GetJsonStr("ForgeGetQueueDataReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ForgeGetQueueDataReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ForgeGetQueueDataReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSyncTeamEntityNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SyncTeamEntityNotify req;
	string jsonstr = GetJsonStr("SyncTeamEntityNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SyncTeamEntityNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SyncTeamEntityNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoServerTimeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ServerTimeNotify req;
	string jsonstr = GetJsonStr("ServerTimeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ServerTimeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ServerTimeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoClientAbilitiesInitFinishCombineNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ClientAbilitiesInitFinishCombineNotify req;
	string jsonstr = GetJsonStr("ClientAbilitiesInitFinishCombineNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ClientAbilitiesInitFinishCombineNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ClientAbilitiesInitFinishCombineNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoQuestDestroyEntityReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::QuestDestroyEntityReq req;
	string jsonstr = GetJsonStr("QuestDestroyEntityReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::QuestDestroyEntityReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" QuestDestroyEntityReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoWorldPlayerLocationNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::WorldPlayerLocationNotify req;
	string jsonstr = GetJsonStr("WorldPlayerLocationNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::WorldPlayerLocationNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" WorldPlayerLocationNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoBackMyWorldReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::BackMyWorldReq req;
	string jsonstr = GetJsonStr("BackMyWorldReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::BackMyWorldReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" BackMyWorldReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerDataNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerDataNotify req;
	string jsonstr = GetJsonStr("PlayerDataNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerDataNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerDataNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonCandidateTeamRefuseNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonCandidateTeamRefuseNotify req;
	string jsonstr = GetJsonStr("DungeonCandidateTeamRefuseNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonCandidateTeamRefuseNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonCandidateTeamRefuseNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonCandidateTeamLeaveReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonCandidateTeamLeaveReq req;
	string jsonstr = GetJsonStr("DungeonCandidateTeamLeaveReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonCandidateTeamLeaveReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonCandidateTeamLeaveReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonWayPointNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonWayPointNotify req;
	string jsonstr = GetJsonStr("DungeonWayPointNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonWayPointNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonWayPointNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerChatNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerChatNotify req;
	string jsonstr = GetJsonStr("PlayerChatNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerChatNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerChatNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEvtAnimatorStateChangedNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EvtAnimatorStateChangedNotify req;
	string jsonstr = GetJsonStr("EvtAnimatorStateChangedNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EvtAnimatorStateChangedNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EvtAnimatorStateChangedNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoWorldPlayerInfoNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::WorldPlayerInfoNotify req;
	string jsonstr = GetJsonStr("WorldPlayerInfoNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::WorldPlayerInfoNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" WorldPlayerInfoNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetCompoundDataReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetCompoundDataReq req;
	string jsonstr = GetJsonStr("GetCompoundDataReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetCompoundDataReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetCompoundDataReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneEntityDrownReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneEntityDrownReq req;
	string jsonstr = GetJsonStr("SceneEntityDrownReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneEntityDrownReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneEntityDrownReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoCookDataNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::CookDataNotify req;
	string jsonstr = GetJsonStr("CookDataNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::CookDataNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" CookDataNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneEntitiesMovesReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneEntitiesMovesReq req;
	string jsonstr = GetJsonStr("SceneEntitiesMovesReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneEntitiesMovesReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneEntitiesMovesReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoMonsterForceAlertNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::MonsterForceAlertNotify req;
	string jsonstr = GetJsonStr("MonsterForceAlertNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::MonsterForceAlertNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" MonsterForceAlertNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAllMarkPointNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AllMarkPointNotify req;
	string jsonstr = GetJsonStr("AllMarkPointNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AllMarkPointNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AllMarkPointNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoTowerMiddleLevelChangeTeamNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::TowerMiddleLevelChangeTeamNotify req;
	string jsonstr = GetJsonStr("TowerMiddleLevelChangeTeamNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::TowerMiddleLevelChangeTeamNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" TowerMiddleLevelChangeTeamNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneKickPlayerNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneKickPlayerNotify req;
	string jsonstr = GetJsonStr("SceneKickPlayerNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneKickPlayerNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneKickPlayerNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneEntitiesMoveCombineNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneEntitiesMoveCombineNotify req;
	string jsonstr = GetJsonStr("SceneEntitiesMoveCombineNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneEntitiesMoveCombineNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneEntitiesMoveCombineNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoOpenStateChangeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::OpenStateChangeNotify req;
	string jsonstr = GetJsonStr("OpenStateChangeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::OpenStateChangeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" OpenStateChangeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSeaLampFlyLampReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SeaLampFlyLampReq req;
	string jsonstr = GetJsonStr("SeaLampFlyLampReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SeaLampFlyLampReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SeaLampFlyLampReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSignInInfoReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SignInInfoReq req;
	string jsonstr = GetJsonStr("SignInInfoReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SignInInfoReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SignInInfoReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoUseItemReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::UseItemReq req;
	string jsonstr = GetJsonStr("UseItemReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::UseItemReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" UseItemReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoFinishedParentQuestNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::FinishedParentQuestNotify req;
	string jsonstr = GetJsonStr("FinishedParentQuestNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::FinishedParentQuestNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" FinishedParentQuestNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEnterSceneReadyReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EnterSceneReadyReq req;
	string jsonstr = GetJsonStr("EnterSceneReadyReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EnterSceneReadyReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EnterSceneReadyReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSetPlayerHeadImageReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SetPlayerHeadImageReq req;
	string jsonstr = GetJsonStr("SetPlayerHeadImageReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SetPlayerHeadImageReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SetPlayerHeadImageReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoRefreshBackgroundAvatarReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::RefreshBackgroundAvatarReq req;
	string jsonstr = GetJsonStr("RefreshBackgroundAvatarReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::RefreshBackgroundAvatarReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" RefreshBackgroundAvatarReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerApplyEnterMpReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerApplyEnterMpReq req;
	string jsonstr = GetJsonStr("PlayerApplyEnterMpReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerApplyEnterMpReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerApplyEnterMpReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoLevelupCityReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::LevelupCityReq req;
	string jsonstr = GetJsonStr("LevelupCityReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::LevelupCityReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" LevelupCityReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoMonsterAlertChangeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::MonsterAlertChangeNotify req;
	string jsonstr = GetJsonStr("MonsterAlertChangeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::MonsterAlertChangeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" MonsterAlertChangeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoResinChangeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ResinChangeNotify req;
	string jsonstr = GetJsonStr("ResinChangeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ResinChangeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ResinChangeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerPropChangeReasonNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerPropChangeReasonNotify req;
	string jsonstr = GetJsonStr("PlayerPropChangeReasonNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerPropChangeReasonNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerPropChangeReasonNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarBuffDelNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarBuffDelNotify req;
	string jsonstr = GetJsonStr("AvatarBuffDelNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarBuffDelNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarBuffDelNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSignInInfoOpenNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SignInInfoOpenNotify req;
	string jsonstr = GetJsonStr("SignInInfoOpenNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SignInInfoOpenNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SignInInfoOpenNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoCutSceneFinishNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::CutSceneFinishNotify req;
	string jsonstr = GetJsonStr("CutSceneFinishNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::CutSceneFinishNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" CutSceneFinishNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoChooseCurAvatarTeamReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ChooseCurAvatarTeamReq req;
	string jsonstr = GetJsonStr("ChooseCurAvatarTeamReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ChooseCurAvatarTeamReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ChooseCurAvatarTeamReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneDataNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneDataNotify req;
	string jsonstr = GetJsonStr("SceneDataNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneDataNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneDataNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoTowerBuffSelectReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::TowerBuffSelectReq req;
	string jsonstr = GetJsonStr("TowerBuffSelectReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::TowerBuffSelectReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" TowerBuffSelectReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoCutSceneBeginNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::CutSceneBeginNotify req;
	string jsonstr = GetJsonStr("CutSceneBeginNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::CutSceneBeginNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" CutSceneBeginNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoWeaponUpgradeReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::WeaponUpgradeReq req;
	string jsonstr = GetJsonStr("WeaponUpgradeReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::WeaponUpgradeReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" WeaponUpgradeReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEvtDestroyGadgetNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EvtDestroyGadgetNotify req;
	string jsonstr = GetJsonStr("EvtDestroyGadgetNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EvtDestroyGadgetNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EvtDestroyGadgetNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoClientPauseNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ClientPauseNotify req;
	string jsonstr = GetJsonStr("ClientPauseNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ClientPauseNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ClientPauseNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGrantRewardNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GrantRewardNotify req;
	string jsonstr = GetJsonStr("GrantRewardNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GrantRewardNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GrantRewardNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerEnterDungeonReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerEnterDungeonReq req;
	string jsonstr = GetJsonStr("PlayerEnterDungeonReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerEnterDungeonReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerEnterDungeonReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneEntityDisappearNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneEntityDisappearNotify req;
	string jsonstr = GetJsonStr("SceneEntityDisappearNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneEntityDisappearNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneEntityDisappearNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonPlayerDieNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonPlayerDieNotify req;
	string jsonstr = GetJsonStr("DungeonPlayerDieNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonPlayerDieNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonPlayerDieNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneAreaExploreNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneAreaExploreNotify req;
	string jsonstr = GetJsonStr("SceneAreaExploreNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneAreaExploreNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneAreaExploreNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarAbilityResetFinishNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarAbilityResetFinishNotify req;
	string jsonstr = GetJsonStr("AvatarAbilityResetFinishNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarAbilityResetFinishNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarAbilityResetFinishNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoBuyResinReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::BuyResinReq req;
	string jsonstr = GetJsonStr("BuyResinReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::BuyResinReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" BuyResinReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoWatcherEventTypeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::WatcherEventTypeNotify req;
	string jsonstr = GetJsonStr("WatcherEventTypeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::WatcherEventTypeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" WatcherEventTypeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoBonusActivityUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::BonusActivityUpdateNotify req;
	string jsonstr = GetJsonStr("BonusActivityUpdateNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::BonusActivityUpdateNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" BonusActivityUpdateNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDealAddFriendReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DealAddFriendReq req;
	string jsonstr = GetJsonStr("DealAddFriendReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DealAddFriendReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DealAddFriendReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEvtAiSyncSkillCdNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EvtAiSyncSkillCdNotify req;
	string jsonstr = GetJsonStr("EvtAiSyncSkillCdNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EvtAiSyncSkillCdNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EvtAiSyncSkillCdNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAddQuestContentProgressReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AddQuestContentProgressReq req;
	string jsonstr = GetJsonStr("AddQuestContentProgressReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AddQuestContentProgressReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AddQuestContentProgressReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonCandidateTeamDismissNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonCandidateTeamDismissNotify req;
	string jsonstr = GetJsonStr("DungeonCandidateTeamDismissNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonCandidateTeamDismissNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonCandidateTeamDismissNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoActivityPlayOpenAnimNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ActivityPlayOpenAnimNotify req;
	string jsonstr = GetJsonStr("ActivityPlayOpenAnimNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ActivityPlayOpenAnimNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ActivityPlayOpenAnimNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneKickPlayerReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneKickPlayerReq req;
	string jsonstr = GetJsonStr("SceneKickPlayerReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneKickPlayerReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneKickPlayerReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEvtAvatarStandUpNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EvtAvatarStandUpNotify req;
	string jsonstr = GetJsonStr("EvtAvatarStandUpNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EvtAvatarStandUpNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EvtAvatarStandUpNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerQuitDungeonReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerQuitDungeonReq req;
	string jsonstr = GetJsonStr("PlayerQuitDungeonReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerQuitDungeonReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerQuitDungeonReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerStoreNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerStoreNotify req;
	string jsonstr = GetJsonStr("PlayerStoreNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerStoreNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerStoreNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonEntryToBeExploreNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonEntryToBeExploreNotify req;
	string jsonstr = GetJsonStr("DungeonEntryToBeExploreNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonEntryToBeExploreNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonEntryToBeExploreNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoBattlePassAllDataNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::BattlePassAllDataNotify req;
	string jsonstr = GetJsonStr("BattlePassAllDataNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::BattlePassAllDataNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" BattlePassAllDataNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEvtRushMoveNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EvtRushMoveNotify req;
	string jsonstr = GetJsonStr("EvtRushMoveNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EvtRushMoveNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EvtRushMoveNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEnterScenePeerNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EnterScenePeerNotify req;
	string jsonstr = GetJsonStr("EnterScenePeerNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EnterScenePeerNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EnterScenePeerNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoMaterialDeleteUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::MaterialDeleteUpdateNotify req;
	string jsonstr = GetJsonStr("MaterialDeleteUpdateNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::MaterialDeleteUpdateNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" MaterialDeleteUpdateNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoTakeInvestigationTargetRewardReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::TakeInvestigationTargetRewardReq req;
	string jsonstr = GetJsonStr("TakeInvestigationTargetRewardReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::TakeInvestigationTargetRewardReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" TakeInvestigationTargetRewardReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonDieOptionReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonDieOptionReq req;
	string jsonstr = GetJsonStr("DungeonDieOptionReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonDieOptionReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonDieOptionReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEntityFightPropNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EntityFightPropNotify req;
	string jsonstr = GetJsonStr("EntityFightPropNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EntityFightPropNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EntityFightPropNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetShopmallDataReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetShopmallDataReq req;
	string jsonstr = GetJsonStr("GetShopmallDataReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetShopmallDataReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetShopmallDataReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonWayPointActivateReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonWayPointActivateReq req;
	string jsonstr = GetJsonStr("DungeonWayPointActivateReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonWayPointActivateReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonWayPointActivateReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarExpeditionDataNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarExpeditionDataNotify req;
	string jsonstr = GetJsonStr("AvatarExpeditionDataNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarExpeditionDataNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarExpeditionDataNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoObstacleModifyNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ObstacleModifyNotify req;
	string jsonstr = GetJsonStr("ObstacleModifyNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ObstacleModifyNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ObstacleModifyNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEvtEntityRenderersChangedNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EvtEntityRenderersChangedNotify req;
	string jsonstr = GetJsonStr("EvtEntityRenderersChangedNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EvtEntityRenderersChangedNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EvtEntityRenderersChangedNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoWorktopOptionNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::WorktopOptionNotify req;
	string jsonstr = GetJsonStr("WorktopOptionNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::WorktopOptionNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" WorktopOptionNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarFetterDataNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarFetterDataNotify req;
	string jsonstr = GetJsonStr("AvatarFetterDataNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarFetterDataNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarFetterDataNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerCookArgsReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerCookArgsReq req;
	string jsonstr = GetJsonStr("PlayerCookArgsReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerCookArgsReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerCookArgsReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoCookRecipeDataNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::CookRecipeDataNotify req;
	string jsonstr = GetJsonStr("CookRecipeDataNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::CookRecipeDataNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" CookRecipeDataNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoScenePointUnlockNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ScenePointUnlockNotify req;
	string jsonstr = GetJsonStr("ScenePointUnlockNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ScenePointUnlockNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ScenePointUnlockNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoWorldOwnerDailyTaskNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::WorldOwnerDailyTaskNotify req;
	string jsonstr = GetJsonStr("WorldOwnerDailyTaskNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::WorldOwnerDailyTaskNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" WorldOwnerDailyTaskNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneEntityAppearNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneEntityAppearNotify req;
	string jsonstr = GetJsonStr("SceneEntityAppearNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneEntityAppearNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneEntityAppearNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarTeamUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarTeamUpdateNotify req;
	string jsonstr = GetJsonStr("AvatarTeamUpdateNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarTeamUpdateNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarTeamUpdateNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoNpcTalkReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::NpcTalkReq req;
	string jsonstr = GetJsonStr("NpcTalkReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::NpcTalkReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" NpcTalkReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEvtAvatarEnterFocusNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EvtAvatarEnterFocusNotify req;
	string jsonstr = GetJsonStr("EvtAvatarEnterFocusNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EvtAvatarEnterFocusNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EvtAvatarEnterFocusNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneTeamUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneTeamUpdateNotify req;
	string jsonstr = GetJsonStr("SceneTeamUpdateNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneTeamUpdateNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneTeamUpdateNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoCookGradeDataNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::CookGradeDataNotify req;
	string jsonstr = GetJsonStr("CookGradeDataNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::CookGradeDataNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" CookGradeDataNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoChangeAvatarReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ChangeAvatarReq req;
	string jsonstr = GetJsonStr("ChangeAvatarReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ChangeAvatarReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ChangeAvatarReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoTowerEnterLevelReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::TowerEnterLevelReq req;
	string jsonstr = GetJsonStr("TowerEnterLevelReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::TowerEnterLevelReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" TowerEnterLevelReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoScenePlayerSoundNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ScenePlayerSoundNotify req;
	string jsonstr = GetJsonStr("ScenePlayerSoundNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ScenePlayerSoundNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ScenePlayerSoundNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoCombineReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::CombineReq req;
	string jsonstr = GetJsonStr("CombineReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::CombineReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" CombineReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEvtBulletDeactiveNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EvtBulletDeactiveNotify req;
	string jsonstr = GetJsonStr("EvtBulletDeactiveNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EvtBulletDeactiveNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EvtBulletDeactiveNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoMarkMapReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::MarkMapReq req;
	string jsonstr = GetJsonStr("MarkMapReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::MarkMapReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" MarkMapReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEnterTransPointRegionNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EnterTransPointRegionNotify req;
	string jsonstr = GetJsonStr("EnterTransPointRegionNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EnterTransPointRegionNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EnterTransPointRegionNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarExpeditionAllDataReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarExpeditionAllDataReq req;
	string jsonstr = GetJsonStr("AvatarExpeditionAllDataReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarExpeditionAllDataReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarExpeditionAllDataReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoWearEquipReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::WearEquipReq req;
	string jsonstr = GetJsonStr("WearEquipReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::WearEquipReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" WearEquipReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoBonusActivityInfoReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::BonusActivityInfoReq req;
	string jsonstr = GetJsonStr("BonusActivityInfoReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::BonusActivityInfoReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" BonusActivityInfoReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoBlossomChestInfoNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::BlossomChestInfoNotify req;
	string jsonstr = GetJsonStr("BlossomChestInfoNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::BlossomChestInfoNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" BlossomChestInfoNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoBattlePassCurScheduleUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::BattlePassCurScheduleUpdateNotify req;
	string jsonstr = GetJsonStr("BattlePassCurScheduleUpdateNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::BattlePassCurScheduleUpdateNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" BattlePassCurScheduleUpdateNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoClientNewMailNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ClientNewMailNotify req;
	string jsonstr = GetJsonStr("ClientNewMailNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ClientNewMailNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ClientNewMailNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEvtEntityStartDieEndNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EvtEntityStartDieEndNotify req;
	string jsonstr = GetJsonStr("EvtEntityStartDieEndNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EvtEntityStartDieEndNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EvtEntityStartDieEndNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoQuestDelNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::QuestDelNotify req;
	string jsonstr = GetJsonStr("QuestDelNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::QuestDelNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" QuestDelNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetSignInRewardReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetSignInRewardReq req;
	string jsonstr = GetJsonStr("GetSignInRewardReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetSignInRewardReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetSignInRewardReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetGachaInfoReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetGachaInfoReq req;
	string jsonstr = GetJsonStr("GetGachaInfoReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetGachaInfoReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetGachaInfoReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoBuyShopmallGoodsReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::BuyShopmallGoodsReq req;
	string jsonstr = GetJsonStr("BuyShopmallGoodsReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::BuyShopmallGoodsReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" BuyShopmallGoodsReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoItemCdGroupTimeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ItemCdGroupTimeNotify req;
	string jsonstr = GetJsonStr("ItemCdGroupTimeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ItemCdGroupTimeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ItemCdGroupTimeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDropItemReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DropItemReq req;
	string jsonstr = GetJsonStr("DropItemReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DropItemReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DropItemReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoTakeInvestigationRewardReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::TakeInvestigationRewardReq req;
	string jsonstr = GetJsonStr("TakeInvestigationRewardReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::TakeInvestigationRewardReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" TakeInvestigationRewardReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoBattlePassMissionUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::BattlePassMissionUpdateNotify req;
	string jsonstr = GetJsonStr("BattlePassMissionUpdateNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::BattlePassMissionUpdateNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" BattlePassMissionUpdateNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoMarkNewNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::MarkNewNotify req;
	string jsonstr = GetJsonStr("MarkNewNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::MarkNewNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" MarkNewNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoCreateMassiveEntityNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::CreateMassiveEntityNotify req;
	string jsonstr = GetJsonStr("CreateMassiveEntityNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::CreateMassiveEntityNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" CreateMassiveEntityNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSealBattleBeginNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SealBattleBeginNotify req;
	string jsonstr = GetJsonStr("SealBattleBeginNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SealBattleBeginNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SealBattleBeginNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoLockWorldFogAreaNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::LockWorldFogAreaNotify req;
	string jsonstr = GetJsonStr("LockWorldFogAreaNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::LockWorldFogAreaNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" LockWorldFogAreaNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAllSeenMonsterNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AllSeenMonsterNotify req;
	string jsonstr = GetJsonStr("AllSeenMonsterNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AllSeenMonsterNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AllSeenMonsterNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAnimatorForceSetAirMoveNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AnimatorForceSetAirMoveNotify req;
	string jsonstr = GetJsonStr("AnimatorForceSetAirMoveNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AnimatorForceSetAirMoveNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AnimatorForceSetAirMoveNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarExpeditionStartReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarExpeditionStartReq req;
	string jsonstr = GetJsonStr("AvatarExpeditionStartReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarExpeditionStartReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarExpeditionStartReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarUnlockTalentNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarUnlockTalentNotify req;
	string jsonstr = GetJsonStr("AvatarUnlockTalentNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarUnlockTalentNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarUnlockTalentNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoWatcherEventNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::WatcherEventNotify req;
	string jsonstr = GetJsonStr("WatcherEventNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::WatcherEventNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" WatcherEventNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAbilityInvocationsNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AbilityInvocationsNotify req;
	string jsonstr = GetJsonStr("AbilityInvocationsNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AbilityInvocationsNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AbilityInvocationsNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlatformRouteStateNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlatformRouteStateNotify req;
	string jsonstr = GetJsonStr("PlatformRouteStateNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlatformRouteStateNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlatformRouteStateNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPostEnterSceneReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PostEnterSceneReq req;
	string jsonstr = GetJsonStr("PostEnterSceneReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PostEnterSceneReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PostEnterSceneReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerLuaShellNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerLuaShellNotify req;
	string jsonstr = GetJsonStr("PlayerLuaShellNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerLuaShellNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerLuaShellNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGmTalkReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GmTalkReq req;
	string jsonstr = GetJsonStr("GmTalkReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GmTalkReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GmTalkReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPushTipsChangeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PushTipsChangeNotify req;
	string jsonstr = GetJsonStr("PushTipsChangeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PushTipsChangeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PushTipsChangeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneRouteChangeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneRouteChangeNotify req;
	string jsonstr = GetJsonStr("SceneRouteChangeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneRouteChangeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneRouteChangeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEntityMoveRoomNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EntityMoveRoomNotify req;
	string jsonstr = GetJsonStr("EntityMoveRoomNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EntityMoveRoomNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EntityMoveRoomNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoTowerLevelEndNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::TowerLevelEndNotify req;
	string jsonstr = GetJsonStr("TowerLevelEndNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::TowerLevelEndNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" TowerLevelEndNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoForgeQueueManipulateReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ForgeQueueManipulateReq req;
	string jsonstr = GetJsonStr("ForgeQueueManipulateReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ForgeQueueManipulateReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ForgeQueueManipulateReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoTowerAllDataReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::TowerAllDataReq req;
	string jsonstr = GetJsonStr("TowerAllDataReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::TowerAllDataReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" TowerAllDataReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetBlossomBriefInfoListReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetBlossomBriefInfoListReq req;
	string jsonstr = GetJsonStr("GetBlossomBriefInfoListReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetBlossomBriefInfoListReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetBlossomBriefInfoListReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetActivityScheduleReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetActivityScheduleReq req;
	string jsonstr = GetJsonStr("GetActivityScheduleReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetActivityScheduleReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetActivityScheduleReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoLifeStateChangeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::LifeStateChangeNotify req;
	string jsonstr = GetJsonStr("LifeStateChangeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::LifeStateChangeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" LifeStateChangeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoRemoveRandTaskInfoNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::RemoveRandTaskInfoNotify req;
	string jsonstr = GetJsonStr("RemoveRandTaskInfoNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::RemoveRandTaskInfoNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" RemoveRandTaskInfoNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerCompoundMaterialReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerCompoundMaterialReq req;
	string jsonstr = GetJsonStr("PlayerCompoundMaterialReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerCompoundMaterialReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerCompoundMaterialReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoTakeoffEquipReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::TakeoffEquipReq req;
	string jsonstr = GetJsonStr("TakeoffEquipReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::TakeoffEquipReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" TakeoffEquipReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoActivityScheduleInfoNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ActivityScheduleInfoNotify req;
	string jsonstr = GetJsonStr("ActivityScheduleInfoNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ActivityScheduleInfoNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ActivityScheduleInfoNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoServerBuffChangeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ServerBuffChangeNotify req;
	string jsonstr = GetJsonStr("ServerBuffChangeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ServerBuffChangeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ServerBuffChangeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSetUpAvatarTeamReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SetUpAvatarTeamReq req;
	string jsonstr = GetJsonStr("SetUpAvatarTeamReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SetUpAvatarTeamReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SetUpAvatarTeamReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoReadMailNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ReadMailNotify req;
	string jsonstr = GetJsonStr("ReadMailNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ReadMailNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ReadMailNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoWindSeedClientNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::WindSeedClientNotify req;
	string jsonstr = GetJsonStr("WindSeedClientNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::WindSeedClientNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" WindSeedClientNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerCookReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerCookReq req;
	string jsonstr = GetJsonStr("PlayerCookReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerCookReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerCookReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEvtDoSkillSuccNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EvtDoSkillSuccNotify req;
	string jsonstr = GetJsonStr("EvtDoSkillSuccNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EvtDoSkillSuccNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EvtDoSkillSuccNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneCreateEntityReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneCreateEntityReq req;
	string jsonstr = GetJsonStr("SceneCreateEntityReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneCreateEntityReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneCreateEntityReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerApplyEnterMpResultNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerApplyEnterMpResultNotify req;
	string jsonstr = GetJsonStr("PlayerApplyEnterMpResultNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerApplyEnterMpResultNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerApplyEnterMpResultNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerChatCDNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerChatCDNotify req;
	string jsonstr = GetJsonStr("PlayerChatCDNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerChatCDNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerChatCDNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonCandidateTeamInviteNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonCandidateTeamInviteNotify req;
	string jsonstr = GetJsonStr("DungeonCandidateTeamInviteNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonCandidateTeamInviteNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonCandidateTeamInviteNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoUnmarkEntityInMinMapNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::UnmarkEntityInMinMapNotify req;
	string jsonstr = GetJsonStr("UnmarkEntityInMinMapNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::UnmarkEntityInMinMapNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" UnmarkEntityInMinMapNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoTakeCompoundOutputReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::TakeCompoundOutputReq req;
	string jsonstr = GetJsonStr("TakeCompoundOutputReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::TakeCompoundOutputReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" TakeCompoundOutputReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoCanUseSkillNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::CanUseSkillNotify req;
	string jsonstr = GetJsonStr("CanUseSkillNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::CanUseSkillNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" CanUseSkillNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEntityForceSyncReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EntityForceSyncReq req;
	string jsonstr = GetJsonStr("EntityForceSyncReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EntityForceSyncReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EntityForceSyncReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoExecuteGadgetLuaReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ExecuteGadgetLuaReq req;
	string jsonstr = GetJsonStr("ExecuteGadgetLuaReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ExecuteGadgetLuaReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ExecuteGadgetLuaReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEnterSceneDoneReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EnterSceneDoneReq req;
	string jsonstr = GetJsonStr("EnterSceneDoneReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EnterSceneDoneReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EnterSceneDoneReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSelectWorktopOptionReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SelectWorktopOptionReq req;
	string jsonstr = GetJsonStr("SelectWorktopOptionReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SelectWorktopOptionReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SelectWorktopOptionReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoBigTalentPointConvertReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::BigTalentPointConvertReq req;
	string jsonstr = GetJsonStr("BigTalentPointConvertReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::BigTalentPointConvertReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" BigTalentPointConvertReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoServerAnnounceNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ServerAnnounceNotify req;
	string jsonstr = GetJsonStr("ServerAnnounceNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ServerAnnounceNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ServerAnnounceNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoQuestUpdateQuestVarReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::QuestUpdateQuestVarReq req;
	string jsonstr = GetJsonStr("QuestUpdateQuestVarReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::QuestUpdateQuestVarReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" QuestUpdateQuestVarReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoTowerLevelStarCondNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::TowerLevelStarCondNotify req;
	string jsonstr = GetJsonStr("TowerLevelStarCondNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::TowerLevelStarCondNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" TowerLevelStarCondNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDestroyMassiveEntityNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DestroyMassiveEntityNotify req;
	string jsonstr = GetJsonStr("DestroyMassiveEntityNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DestroyMassiveEntityNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DestroyMassiveEntityNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoCutSceneEndNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::CutSceneEndNotify req;
	string jsonstr = GetJsonStr("CutSceneEndNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::CutSceneEndNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" CutSceneEndNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonFollowNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonFollowNotify req;
	string jsonstr = GetJsonStr("DungeonFollowNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonFollowNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonFollowNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneAvatarStaminaStepReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneAvatarStaminaStepReq req;
	string jsonstr = GetJsonStr("SceneAvatarStaminaStepReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneAvatarStaminaStepReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneAvatarStaminaStepReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetPlayerMpModeAvailabilityReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetPlayerMpModeAvailabilityReq req;
	string jsonstr = GetJsonStr("GetPlayerMpModeAvailabilityReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetPlayerMpModeAvailabilityReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetPlayerMpModeAvailabilityReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarAddNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarAddNotify req;
	string jsonstr = GetJsonStr("AvatarAddNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarAddNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarAddNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoWatcherChangeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::WatcherChangeNotify req;
	string jsonstr = GetJsonStr("WatcherChangeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::WatcherChangeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" WatcherChangeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarSkillMaxChargeCountNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarSkillMaxChargeCountNotify req;
	string jsonstr = GetJsonStr("AvatarSkillMaxChargeCountNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarSkillMaxChargeCountNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarSkillMaxChargeCountNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonCandidateTeamInviteReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonCandidateTeamInviteReq req;
	string jsonstr = GetJsonStr("DungeonCandidateTeamInviteReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonCandidateTeamInviteReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonCandidateTeamInviteReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEvtBulletHitNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EvtBulletHitNotify req;
	string jsonstr = GetJsonStr("EvtBulletHitNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EvtBulletHitNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EvtBulletHitNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEvtAiSyncCombatThreatInfoNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EvtAiSyncCombatThreatInfoNotify req;
	string jsonstr = GetJsonStr("EvtAiSyncCombatThreatInfoNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EvtAiSyncCombatThreatInfoNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EvtAiSyncCombatThreatInfoNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoWorldOwnerBlossomBriefInfoNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::WorldOwnerBlossomBriefInfoNotify req;
	string jsonstr = GetJsonStr("WorldOwnerBlossomBriefInfoNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::WorldOwnerBlossomBriefInfoNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" WorldOwnerBlossomBriefInfoNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoOrderFinishNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::OrderFinishNotify req;
	string jsonstr = GetJsonStr("OrderFinishNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::OrderFinishNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" OrderFinishNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoCombatInvocationsNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::CombatInvocationsNotify req;
	string jsonstr = GetJsonStr("CombatInvocationsNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::CombatInvocationsNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" CombatInvocationsNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoWeaponAwakenReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::WeaponAwakenReq req;
	string jsonstr = GetJsonStr("WeaponAwakenReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::WeaponAwakenReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" WeaponAwakenReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoOpenStateUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::OpenStateUpdateNotify req;
	string jsonstr = GetJsonStr("OpenStateUpdateNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::OpenStateUpdateNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" OpenStateUpdateNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoTakePlayerLevelRewardReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::TakePlayerLevelRewardReq req;
	string jsonstr = GetJsonStr("TakePlayerLevelRewardReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::TakePlayerLevelRewardReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" TakePlayerLevelRewardReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoWorldPlayerDieNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::WorldPlayerDieNotify req;
	string jsonstr = GetJsonStr("WorldPlayerDieNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::WorldPlayerDieNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" WorldPlayerDieNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarEnterElementViewNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarEnterElementViewNotify req;
	string jsonstr = GetJsonStr("AvatarEnterElementViewNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarEnterElementViewNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarEnterElementViewNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarSkillChangeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarSkillChangeNotify req;
	string jsonstr = GetJsonStr("AvatarSkillChangeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarSkillChangeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarSkillChangeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerQuitFromMpNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerQuitFromMpNotify req;
	string jsonstr = GetJsonStr("PlayerQuitFromMpNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerQuitFromMpNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerQuitFromMpNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAskAddFriendReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AskAddFriendReq req;
	string jsonstr = GetJsonStr("AskAddFriendReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AskAddFriendReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AskAddFriendReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAddSeenMonsterNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AddSeenMonsterNotify req;
	string jsonstr = GetJsonStr("AddSeenMonsterNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AddSeenMonsterNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AddSeenMonsterNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarFightPropNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarFightPropNotify req;
	string jsonstr = GetJsonStr("AvatarFightPropNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarFightPropNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarFightPropNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoChangeTeamNameReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ChangeTeamNameReq req;
	string jsonstr = GetJsonStr("ChangeTeamNameReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ChangeTeamNameReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ChangeTeamNameReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoStoreWeightLimitNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::StoreWeightLimitNotify req;
	string jsonstr = GetJsonStr("StoreWeightLimitNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::StoreWeightLimitNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" StoreWeightLimitNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDailyTaskProgressNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DailyTaskProgressNotify req;
	string jsonstr = GetJsonStr("DailyTaskProgressNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DailyTaskProgressNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DailyTaskProgressNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarAbilityResetNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarAbilityResetNotify req;
	string jsonstr = GetJsonStr("AvatarAbilityResetNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarAbilityResetNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarAbilityResetNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerEnterSceneNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerEnterSceneNotify req;
	string jsonstr = GetJsonStr("PlayerEnterSceneNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerEnterSceneNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerEnterSceneNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerInvestigationTargetNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerInvestigationTargetNotify req;
	string jsonstr = GetJsonStr("PlayerInvestigationTargetNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerInvestigationTargetNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerInvestigationTargetNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoBlossomBriefInfoNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::BlossomBriefInfoNotify req;
	string jsonstr = GetJsonStr("BlossomBriefInfoNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::BlossomBriefInfoNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" BlossomBriefInfoNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoTowerDailyRewardProgressChangeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::TowerDailyRewardProgressChangeNotify req;
	string jsonstr = GetJsonStr("TowerDailyRewardProgressChangeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::TowerDailyRewardProgressChangeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" TowerDailyRewardProgressChangeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoChallengeDataNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ChallengeDataNotify req;
	string jsonstr = GetJsonStr("ChallengeDataNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ChallengeDataNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ChallengeDataNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetShopmallShopDataReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetShopmallShopDataReq req;
	string jsonstr = GetJsonStr("GetShopmallShopDataReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetShopmallShopDataReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetShopmallShopDataReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonShowReminderNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonShowReminderNotify req;
	string jsonstr = GetJsonStr("DungeonShowReminderNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonShowReminderNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonShowReminderNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoWeaponPromoteReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::WeaponPromoteReq req;
	string jsonstr = GetJsonStr("WeaponPromoteReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::WeaponPromoteReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" WeaponPromoteReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPushTipsReadFinishReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PushTipsReadFinishReq req;
	string jsonstr = GetJsonStr("PushTipsReadFinishReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PushTipsReadFinishReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PushTipsReadFinishReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoClientTriggerEventNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ClientTriggerEventNotify req;
	string jsonstr = GetJsonStr("ClientTriggerEventNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ClientTriggerEventNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ClientTriggerEventNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGivingRecordNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GivingRecordNotify req;
	string jsonstr = GetJsonStr("GivingRecordNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GivingRecordNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GivingRecordNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerApplyEnterMpResultReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerApplyEnterMpResultReq req;
	string jsonstr = GetJsonStr("PlayerApplyEnterMpResultReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerApplyEnterMpResultReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerApplyEnterMpResultReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoProudSkillChangeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ProudSkillChangeNotify req;
	string jsonstr = GetJsonStr("ProudSkillChangeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ProudSkillChangeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ProudSkillChangeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoQuestUpdateQuestVarNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::QuestUpdateQuestVarNotify req;
	string jsonstr = GetJsonStr("QuestUpdateQuestVarNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::QuestUpdateQuestVarNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" QuestUpdateQuestVarNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneDestroyEntityReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneDestroyEntityReq req;
	string jsonstr = GetJsonStr("SceneDestroyEntityReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneDestroyEntityReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneDestroyEntityReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetAllMailReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetAllMailReq req;
	string jsonstr = GetJsonStr("GetAllMailReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetAllMailReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetAllMailReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSetPlayerBornDataReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SetPlayerBornDataReq req;
	string jsonstr = GetJsonStr("SetPlayerBornDataReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SetPlayerBornDataReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SetPlayerBornDataReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDropSubfieldReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DropSubfieldReq req;
	string jsonstr = GetJsonStr("DropSubfieldReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DropSubfieldReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DropSubfieldReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoBattlePassMissionDelNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::BattlePassMissionDelNotify req;
	string jsonstr = GetJsonStr("BattlePassMissionDelNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::BattlePassMissionDelNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" BattlePassMissionDelNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoHostPlayerNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::HostPlayerNotify req;
	string jsonstr = GetJsonStr("HostPlayerNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::HostPlayerNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" HostPlayerNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarSkillInfoNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarSkillInfoNotify req;
	string jsonstr = GetJsonStr("AvatarSkillInfoNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarSkillInfoNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarSkillInfoNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoWorldResinChangeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::WorldResinChangeNotify req;
	string jsonstr = GetJsonStr("WorldResinChangeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::WorldResinChangeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" WorldResinChangeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetSceneAreaReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetSceneAreaReq req;
	string jsonstr = GetJsonStr("GetSceneAreaReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetSceneAreaReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetSceneAreaReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoScenePlayerLocationNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ScenePlayerLocationNotify req;
	string jsonstr = GetJsonStr("ScenePlayerLocationNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ScenePlayerLocationNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ScenePlayerLocationNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarDelNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarDelNotify req;
	string jsonstr = GetJsonStr("AvatarDelNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarDelNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarDelNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoWorldDataNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::WorldDataNotify req;
	string jsonstr = GetJsonStr("WorldDataNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::WorldDataNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" WorldDataNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoRobotPushPlayerDataNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::RobotPushPlayerDataNotify req;
	string jsonstr = GetJsonStr("RobotPushPlayerDataNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::RobotPushPlayerDataNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" RobotPushPlayerDataNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoTowerCurLevelRecordChangeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::TowerCurLevelRecordChangeNotify req;
	string jsonstr = GetJsonStr("TowerCurLevelRecordChangeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::TowerCurLevelRecordChangeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" TowerCurLevelRecordChangeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneInitFinishReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneInitFinishReq req;
	string jsonstr = GetJsonStr("SceneInitFinishReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneInitFinishReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneInitFinishReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoQuestListNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::QuestListNotify req;
	string jsonstr = GetJsonStr("QuestListNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::QuestListNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" QuestListNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoFocusAvatarReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::FocusAvatarReq req;
	string jsonstr = GetJsonStr("FocusAvatarReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::FocusAvatarReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" FocusAvatarReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoTakeMaterialDeleteReturnReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::TakeMaterialDeleteReturnReq req;
	string jsonstr = GetJsonStr("TakeMaterialDeleteReturnReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::TakeMaterialDeleteReturnReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" TakeMaterialDeleteReturnReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneAreaUnlockNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneAreaUnlockNotify req;
	string jsonstr = GetJsonStr("SceneAreaUnlockNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneAreaUnlockNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneAreaUnlockNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetAuthkeyReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetAuthkeyReq req;
	string jsonstr = GetJsonStr("GetAuthkeyReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetAuthkeyReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetAuthkeyReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoBargainStartNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::BargainStartNotify req;
	string jsonstr = GetJsonStr("BargainStartNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::BargainStartNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" BargainStartNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonCandidateTeamSetReadyReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonCandidateTeamSetReadyReq req;
	string jsonstr = GetJsonStr("DungeonCandidateTeamSetReadyReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonCandidateTeamSetReadyReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonCandidateTeamSetReadyReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneTeamMPDisplayCurAvatarNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneTeamMPDisplayCurAvatarNotify req;
	string jsonstr = GetJsonStr("SceneTeamMPDisplayCurAvatarNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneTeamMPDisplayCurAvatarNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneTeamMPDisplayCurAvatarNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonChallengeBeginNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonChallengeBeginNotify req;
	string jsonstr = GetJsonStr("DungeonChallengeBeginNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonChallengeBeginNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonChallengeBeginNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEnterWorldAreaReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EnterWorldAreaReq req;
	string jsonstr = GetJsonStr("EnterWorldAreaReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EnterWorldAreaReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EnterWorldAreaReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonCandidateTeamInfoNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonCandidateTeamInfoNotify req;
	string jsonstr = GetJsonStr("DungeonCandidateTeamInfoNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonCandidateTeamInfoNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonCandidateTeamInfoNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEndCameraSceneLookNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EndCameraSceneLookNotify req;
	string jsonstr = GetJsonStr("EndCameraSceneLookNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EndCameraSceneLookNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EndCameraSceneLookNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoTriggerCreateGadgetToEquipPartNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::TriggerCreateGadgetToEquipPartNotify req;
	string jsonstr = GetJsonStr("TriggerCreateGadgetToEquipPartNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::TriggerCreateGadgetToEquipPartNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" TriggerCreateGadgetToEquipPartNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerSetLanguageReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerSetLanguageReq req;
	string jsonstr = GetJsonStr("PlayerSetLanguageReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerSetLanguageReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerSetLanguageReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneEntityMoveNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneEntityMoveNotify req;
	string jsonstr = GetJsonStr("SceneEntityMoveNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneEntityMoveNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneEntityMoveNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoClientTransmitReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ClientTransmitReq req;
	string jsonstr = GetJsonStr("ClientTransmitReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ClientTransmitReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ClientTransmitReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoQuestListUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::QuestListUpdateNotify req;
	string jsonstr = GetJsonStr("QuestListUpdateNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::QuestListUpdateNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" QuestListUpdateNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPingReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PingReq req;
	string jsonstr = GetJsonStr("PingReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PingReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PingReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarPromoteReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarPromoteReq req;
	string jsonstr = GetJsonStr("AvatarPromoteReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarPromoteReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarPromoteReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetDailyDungeonEntryInfoReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetDailyDungeonEntryInfoReq req;
	string jsonstr = GetJsonStr("GetDailyDungeonEntryInfoReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetDailyDungeonEntryInfoReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetDailyDungeonEntryInfoReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneAreaWeatherNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneAreaWeatherNotify req;
	string jsonstr = GetJsonStr("SceneAreaWeatherNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneAreaWeatherNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneAreaWeatherNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerApplyEnterMpNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerApplyEnterMpNotify req;
	string jsonstr = GetJsonStr("PlayerApplyEnterMpNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerApplyEnterMpNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerApplyEnterMpNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoBonusActivityAllDataNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::BonusActivityAllDataNotify req;
	string jsonstr = GetJsonStr("BonusActivityAllDataNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::BonusActivityAllDataNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" BonusActivityAllDataNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerGameTimeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerGameTimeNotify req;
	string jsonstr = GetJsonStr("PlayerGameTimeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerGameTimeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerGameTimeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoItemGivingReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ItemGivingReq req;
	string jsonstr = GetJsonStr("ItemGivingReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ItemGivingReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ItemGivingReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoQuestCreateEntityReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::QuestCreateEntityReq req;
	string jsonstr = GetJsonStr("QuestCreateEntityReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::QuestCreateEntityReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" QuestCreateEntityReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEvtAvatarExitFocusNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EvtAvatarExitFocusNotify req;
	string jsonstr = GetJsonStr("EvtAvatarExitFocusNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EvtAvatarExitFocusNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EvtAvatarExitFocusNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoTowerGetFloorStarRewardReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::TowerGetFloorStarRewardReq req;
	string jsonstr = GetJsonStr("TowerGetFloorStarRewardReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::TowerGetFloorStarRewardReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" TowerGetFloorStarRewardReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSeaLampTakeContributionRewardReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SeaLampTakeContributionRewardReq req;
	string jsonstr = GetJsonStr("SeaLampTakeContributionRewardReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SeaLampTakeContributionRewardReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SeaLampTakeContributionRewardReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerRandomCookReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerRandomCookReq req;
	string jsonstr = GetJsonStr("PlayerRandomCookReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerRandomCookReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerRandomCookReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonSlipRevivePointActivateReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonSlipRevivePointActivateReq req;
	string jsonstr = GetJsonStr("DungeonSlipRevivePointActivateReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonSlipRevivePointActivateReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonSlipRevivePointActivateReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoLogCutsceneNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::LogCutsceneNotify req;
	string jsonstr = GetJsonStr("LogCutsceneNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::LogCutsceneNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" LogCutsceneNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoServerAnnounceRevokeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ServerAnnounceRevokeNotify req;
	string jsonstr = GetJsonStr("ServerAnnounceRevokeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ServerAnnounceRevokeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ServerAnnounceRevokeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetBonusActivityRewardReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetBonusActivityRewardReq req;
	string jsonstr = GetJsonStr("GetBonusActivityRewardReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetBonusActivityRewardReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetBonusActivityRewardReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoQuestDestroyNpcReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::QuestDestroyNpcReq req;
	string jsonstr = GetJsonStr("QuestDestroyNpcReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::QuestDestroyNpcReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" QuestDestroyNpcReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGMShowNavMeshReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GMShowNavMeshReq req;
	string jsonstr = GetJsonStr("GMShowNavMeshReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GMShowNavMeshReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GMShowNavMeshReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneForceUnlockNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneForceUnlockNotify req;
	string jsonstr = GetJsonStr("SceneForceUnlockNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneForceUnlockNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneForceUnlockNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerPreEnterMpNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerPreEnterMpNotify req;
	string jsonstr = GetJsonStr("PlayerPreEnterMpNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerPreEnterMpNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerPreEnterMpNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDelMailReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DelMailReq req;
	string jsonstr = GetJsonStr("DelMailReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DelMailReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DelMailReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoServerLogNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ServerLogNotify req;
	string jsonstr = GetJsonStr("ServerLogNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ServerLogNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ServerLogNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarPropNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarPropNotify req;
	string jsonstr = GetJsonStr("AvatarPropNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarPropNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarPropNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoMassiveEntityStateChangedNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::MassiveEntityStateChangedNotify req;
	string jsonstr = GetJsonStr("MassiveEntityStateChangedNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::MassiveEntityStateChangedNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" MassiveEntityStateChangedNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetInvestigationMonsterReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetInvestigationMonsterReq req;
	string jsonstr = GetJsonStr("GetInvestigationMonsterReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetInvestigationMonsterReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetInvestigationMonsterReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoFinishedParentQuestUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::FinishedParentQuestUpdateNotify req;
	string jsonstr = GetJsonStr("FinishedParentQuestUpdateNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::FinishedParentQuestUpdateNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" FinishedParentQuestUpdateNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonSettleNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonSettleNotify req;
	string jsonstr = GetJsonStr("DungeonSettleNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonSettleNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonSettleNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEntityAuthorityChangeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EntityAuthorityChangeNotify req;
	string jsonstr = GetJsonStr("EntityAuthorityChangeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EntityAuthorityChangeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EntityAuthorityChangeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarSkillUpgradeReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarSkillUpgradeReq req;
	string jsonstr = GetJsonStr("AvatarSkillUpgradeReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarSkillUpgradeReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarSkillUpgradeReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerPropChangeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerPropChangeNotify req;
	string jsonstr = GetJsonStr("PlayerPropChangeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerPropChangeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerPropChangeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonPlayerDieReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonPlayerDieReq req;
	string jsonstr = GetJsonStr("DungeonPlayerDieReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonPlayerDieReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonPlayerDieReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarExpeditionCallBackReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarExpeditionCallBackReq req;
	string jsonstr = GetJsonStr("AvatarExpeditionCallBackReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarExpeditionCallBackReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarExpeditionCallBackReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoExecuteGroupTriggerReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ExecuteGroupTriggerReq req;
	string jsonstr = GetJsonStr("ExecuteGroupTriggerReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ExecuteGroupTriggerReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ExecuteGroupTriggerReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetOnlinePlayerListReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetOnlinePlayerListReq req;
	string jsonstr = GetJsonStr("GetOnlinePlayerListReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetOnlinePlayerListReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetOnlinePlayerListReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoRechargeReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::RechargeReq req;
	string jsonstr = GetJsonStr("RechargeReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::RechargeReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" RechargeReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoChangeMpTeamAvatarReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ChangeMpTeamAvatarReq req;
	string jsonstr = GetJsonStr("ChangeMpTeamAvatarReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ChangeMpTeamAvatarReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ChangeMpTeamAvatarReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetShopReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetShopReq req;
	string jsonstr = GetJsonStr("GetShopReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetShopReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetShopReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetPlayerFriendListReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetPlayerFriendListReq req;
	string jsonstr = GetJsonStr("GetPlayerFriendListReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetPlayerFriendListReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetPlayerFriendListReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoBuyWorldResinReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::BuyWorldResinReq req;
	string jsonstr = GetJsonStr("BuyWorldResinReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::BuyWorldResinReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" BuyWorldResinReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSetPlayerNameReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SetPlayerNameReq req;
	string jsonstr = GetJsonStr("SetPlayerNameReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SetPlayerNameReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SetPlayerNameReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoServerDisconnectClientNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ServerDisconnectClientNotify req;
	string jsonstr = GetJsonStr("ServerDisconnectClientNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ServerDisconnectClientNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ServerDisconnectClientNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSeaLampContributeItemReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SeaLampContributeItemReq req;
	string jsonstr = GetJsonStr("SeaLampContributeItemReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SeaLampContributeItemReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SeaLampContributeItemReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneTimeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneTimeNotify req;
	string jsonstr = GetJsonStr("SceneTimeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneTimeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneTimeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoScenePlayerInfoNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ScenePlayerInfoNotify req;
	string jsonstr = GetJsonStr("ScenePlayerInfoNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ScenePlayerInfoNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ScenePlayerInfoNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoKeepAliveNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::KeepAliveNotify req;
	string jsonstr = GetJsonStr("KeepAliveNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::KeepAliveNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" KeepAliveNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEvtBeingHitsCombineNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EvtBeingHitsCombineNotify req;
	string jsonstr = GetJsonStr("EvtBeingHitsCombineNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EvtBeingHitsCombineNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EvtBeingHitsCombineNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoClientAbilityInitFinishNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ClientAbilityInitFinishNotify req;
	string jsonstr = GetJsonStr("ClientAbilityInitFinishNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ClientAbilityInitFinishNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ClientAbilityInitFinishNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarBuffAddNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarBuffAddNotify req;
	string jsonstr = GetJsonStr("AvatarBuffAddNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarBuffAddNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarBuffAddNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneEntityMoveReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneEntityMoveReq req;
	string jsonstr = GetJsonStr("SceneEntityMoveReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneEntityMoveReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneEntityMoveReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoExitTransPointRegionNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ExitTransPointRegionNotify req;
	string jsonstr = GetJsonStr("ExitTransPointRegionNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ExitTransPointRegionNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ExitTransPointRegionNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerInvestigationAllInfoNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerInvestigationAllInfoNotify req;
	string jsonstr = GetJsonStr("PlayerInvestigationAllInfoNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerInvestigationAllInfoNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerInvestigationAllInfoNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonEntryInfoReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonEntryInfoReq req;
	string jsonstr = GetJsonStr("DungeonEntryInfoReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonEntryInfoReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonEntryInfoReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetQuestTalkHistoryReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetQuestTalkHistoryReq req;
	string jsonstr = GetJsonStr("GetQuestTalkHistoryReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetQuestTalkHistoryReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetQuestTalkHistoryReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSetPlayerPropReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SetPlayerPropReq req;
	string jsonstr = GetJsonStr("SetPlayerPropReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SetPlayerPropReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SetPlayerPropReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoExitSceneWeatherAreaNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ExitSceneWeatherAreaNotify req;
	string jsonstr = GetJsonStr("ExitSceneWeatherAreaNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ExitSceneWeatherAreaNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ExitSceneWeatherAreaNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDeleteFriendReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DeleteFriendReq req;
	string jsonstr = GetJsonStr("DeleteFriendReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DeleteFriendReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DeleteFriendReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoMonsterSummonTagNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::MonsterSummonTagNotify req;
	string jsonstr = GetJsonStr("MonsterSummonTagNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::MonsterSummonTagNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" MonsterSummonTagNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoActivityInfoNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ActivityInfoNotify req;
	string jsonstr = GetJsonStr("ActivityInfoNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ActivityInfoNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ActivityInfoNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEvtCostStaminaNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EvtCostStaminaNotify req;
	string jsonstr = GetJsonStr("EvtCostStaminaNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EvtCostStaminaNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EvtCostStaminaNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoChatHistoryNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ChatHistoryNotify req;
	string jsonstr = GetJsonStr("ChatHistoryNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ChatHistoryNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ChatHistoryNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonCandidateTeamReplyInviteReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonCandidateTeamReplyInviteReq req;
	string jsonstr = GetJsonStr("DungeonCandidateTeamReplyInviteReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonCandidateTeamReplyInviteReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonCandidateTeamReplyInviteReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSeeMonsterReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SeeMonsterReq req;
	string jsonstr = GetJsonStr("SeeMonsterReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SeeMonsterReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SeeMonsterReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSealBattleEndNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SealBattleEndNotify req;
	string jsonstr = GetJsonStr("SealBattleEndNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SealBattleEndNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SealBattleEndNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoTowerBriefDataNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::TowerBriefDataNotify req;
	string jsonstr = GetJsonStr("TowerBriefDataNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::TowerBriefDataNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" TowerBriefDataNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoProudSkillExtraLevelNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ProudSkillExtraLevelNotify req;
	string jsonstr = GetJsonStr("ProudSkillExtraLevelNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ProudSkillExtraLevelNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ProudSkillExtraLevelNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPersonalSceneJumpReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PersonalSceneJumpReq req;
	string jsonstr = GetJsonStr("PersonalSceneJumpReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PersonalSceneJumpReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PersonalSceneJumpReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerEnterSceneInfoNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerEnterSceneInfoNotify req;
	string jsonstr = GetJsonStr("PlayerEnterSceneInfoNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerEnterSceneInfoNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerEnterSceneInfoNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAbilityInvocationFixedNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AbilityInvocationFixedNotify req;
	string jsonstr = GetJsonStr("AbilityInvocationFixedNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AbilityInvocationFixedNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AbilityInvocationFixedNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoClientReconnectNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ClientReconnectNotify req;
	string jsonstr = GetJsonStr("ClientReconnectNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ClientReconnectNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ClientReconnectNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarSkillDepotChangeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarSkillDepotChangeNotify req;
	string jsonstr = GetJsonStr("AvatarSkillDepotChangeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarSkillDepotChangeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarSkillDepotChangeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneGetAreaExplorePercentReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneGetAreaExplorePercentReq req;
	string jsonstr = GetJsonStr("SceneGetAreaExplorePercentReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneGetAreaExplorePercentReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneGetAreaExplorePercentReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEvtAnimatorParameterNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EvtAnimatorParameterNotify req;
	string jsonstr = GetJsonStr("EvtAnimatorParameterNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EvtAnimatorParameterNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EvtAnimatorParameterNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoLoadActivityTerrainNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::LoadActivityTerrainNotify req;
	string jsonstr = GetJsonStr("LoadActivityTerrainNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::LoadActivityTerrainNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" LoadActivityTerrainNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonDataNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonDataNotify req;
	string jsonstr = GetJsonStr("DungeonDataNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonDataNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonDataNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetScenePointReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetScenePointReq req;
	string jsonstr = GetJsonStr("GetScenePointReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetScenePointReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetScenePointReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSeaLampTakePhaseRewardReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SeaLampTakePhaseRewardReq req;
	string jsonstr = GetJsonStr("SeaLampTakePhaseRewardReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SeaLampTakePhaseRewardReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SeaLampTakePhaseRewardReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoUnlockAvatarTalentReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::UnlockAvatarTalentReq req;
	string jsonstr = GetJsonStr("UnlockAvatarTalentReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::UnlockAvatarTalentReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" UnlockAvatarTalentReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGadgetStateNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GadgetStateNotify req;
	string jsonstr = GetJsonStr("GadgetStateNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GadgetStateNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GadgetStateNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarUpgradeReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarUpgradeReq req;
	string jsonstr = GetJsonStr("AvatarUpgradeReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarUpgradeReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarUpgradeReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEvtFaceToDirNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EvtFaceToDirNotify req;
	string jsonstr = GetJsonStr("EvtFaceToDirNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EvtFaceToDirNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EvtFaceToDirNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDungeonGetStatueDropReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DungeonGetStatueDropReq req;
	string jsonstr = GetJsonStr("DungeonGetStatueDropReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DungeonGetStatueDropReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DungeonGetStatueDropReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlatformStartRouteNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlatformStartRouteNotify req;
	string jsonstr = GetJsonStr("PlatformStartRouteNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlatformStartRouteNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlatformStartRouteNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGadgetInteractReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GadgetInteractReq req;
	string jsonstr = GetJsonStr("GadgetInteractReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GadgetInteractReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GadgetInteractReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDailyTaskScoreRewardNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DailyTaskScoreRewardNotify req;
	string jsonstr = GetJsonStr("DailyTaskScoreRewardNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DailyTaskScoreRewardNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DailyTaskScoreRewardNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEntityPropNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EntityPropNotify req;
	string jsonstr = GetJsonStr("EntityPropNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EntityPropNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EntityPropNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSceneWeatherForcastReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SceneWeatherForcastReq req;
	string jsonstr = GetJsonStr("SceneWeatherForcastReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SceneWeatherForcastReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SceneWeatherForcastReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoMailChangeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::MailChangeNotify req;
	string jsonstr = GetJsonStr("MailChangeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::MailChangeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" MailChangeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetActivityInfoReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetActivityInfoReq req;
	string jsonstr = GetJsonStr("GetActivityInfoReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetActivityInfoReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetActivityInfoReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEvtFaceToEntityNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EvtFaceToEntityNotify req;
	string jsonstr = GetJsonStr("EvtFaceToEntityNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EvtFaceToEntityNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EvtFaceToEntityNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoChapterStateNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ChapterStateNotify req;
	string jsonstr = GetJsonStr("ChapterStateNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ChapterStateNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ChapterStateNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerChatReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerChatReq req;
	string jsonstr = GetJsonStr("PlayerChatReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerChatReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerChatReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoBossChestActivateNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::BossChestActivateNotify req;
	string jsonstr = GetJsonStr("BossChestActivateNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::BossChestActivateNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" BossChestActivateNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoTowerSurrenderReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::TowerSurrenderReq req;
	string jsonstr = GetJsonStr("TowerSurrenderReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::TowerSurrenderReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" TowerSurrenderReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoEvtAvatarUpdateFocusNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::EvtAvatarUpdateFocusNotify req;
	string jsonstr = GetJsonStr("EvtAvatarUpdateFocusNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::EvtAvatarUpdateFocusNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" EvtAvatarUpdateFocusNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoClientReportNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ClientReportNotify req;
	string jsonstr = GetJsonStr("ClientReportNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ClientReportNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ClientReportNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoPlayerTimeNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::PlayerTimeNotify req;
	string jsonstr = GetJsonStr("PlayerTimeNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::PlayerTimeNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" PlayerTimeNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAbilityInvocationFailNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AbilityInvocationFailNotify req;
	string jsonstr = GetJsonStr("AbilityInvocationFailNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AbilityInvocationFailNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AbilityInvocationFailNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoReliquaryUpgradeReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ReliquaryUpgradeReq req;
	string jsonstr = GetJsonStr("ReliquaryUpgradeReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ReliquaryUpgradeReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ReliquaryUpgradeReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoSignInAllDataNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::SignInAllDataNotify req;
	string jsonstr = GetJsonStr("SignInAllDataNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::SignInAllDataNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" SignInAllDataNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDataResVersionNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DataResVersionNotify req;
	string jsonstr = GetJsonStr("DataResVersionNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DataResVersionNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DataResVersionNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDelTeamEntityNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DelTeamEntityNotify req;
	string jsonstr = GetJsonStr("DelTeamEntityNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DelTeamEntityNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DelTeamEntityNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoProudSkillUpgradeReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::ProudSkillUpgradeReq req;
	string jsonstr = GetJsonStr("ProudSkillUpgradeReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::ProudSkillUpgradeReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" ProudSkillUpgradeReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarExpeditionGetRewardReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarExpeditionGetRewardReq req;
	string jsonstr = GetJsonStr("AvatarExpeditionGetRewardReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarExpeditionGetRewardReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarExpeditionGetRewardReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoAvatarDieAnimationEndReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::AvatarDieAnimationEndReq req;
	string jsonstr = GetJsonStr("AvatarDieAnimationEndReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::AvatarDieAnimationEndReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" AvatarDieAnimationEndReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoGetSceneNpcPositionReq(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::GetSceneNpcPositionReq req;
	string jsonstr = GetJsonStr("GetSceneNpcPositionReq");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::GetSceneNpcPositionReq_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" GetSceneNpcPositionReq\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoDropHintNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::DropHintNotify req;
	string jsonstr = GetJsonStr("DropHintNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::DropHintNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" DropHintNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

int CG4GameScriptOp::DoCompoundDataNotify(unsigned int dwUin, STScriptOpParam *pParam)
{
	string data_pb;

	proto::CompoundDataNotify req;
	string jsonstr = GetJsonStr("CompoundDataNotify");
	google::protobuf::util::JsonStringToMessage(jsonstr, &req);

	unsigned short wCmdID = proto::CompoundDataNotify_CmdId_CMD_ID;

	PackProtobuf(dwUin, wCmdID, req, data_pb);
	string debug_str;
	google::protobuf::util::MessageToJsonString(req, &debug_str,option);
	debug_str = "\n<send>\n"+string(GetCurDateTimeCStr(NULL))+" CompoundDataNotify\n" + debug_str + "</send>"
;	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return SendPkg(dwUin, wCmdID, pParam, data_pb.length());
}

