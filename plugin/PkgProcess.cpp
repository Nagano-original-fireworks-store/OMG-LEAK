#include "PkgProcess.h"
#include "facadeplatform_i.h"
#include "Pack.h"
#include "Trans.h"
#include <google/protobuf/service.h>
#include <google/protobuf/text_format.h>
#include <google/protobuf/util/json_util.h>
#include <math.h>  
#include <time.h>
#include <vector>
//#include "define.pb.h"
//#include "player.pb.h"
#include "Hk4eProto.h"
#include "UserInfo.h"
#include "packet.h"


CG4GameProcess::CG4GameProcess()
{
	init(m_mapMsgHandler);
	//初始化各种自定义变量
	option.add_whitespace=true;
	option.preserve_proto_field_names=true;
	option.always_print_primitive_fields=true;
}

CG4GameProcess::~CG4GameProcess(){
	return;
}

int CG4GameProcess::GetHeaderLen()
{
	return 0;
}

//根据msgID分发不同消息
unsigned CG4GameProcess::StoreProtocolID(unsigned dwUin, void *pPkg, size_t uPkgSize)
{
	//重置收包msgID
	m_packet.cmd_id_=0;
	//使用packet打解包类，解出包中的cmd_id
	m_packet.parseFromArray((char *)pPkg, uPkgSize);
	//打印日志
	m_poFacadePlatform->TestLog(dwUin, "StoreProtocolID recv len: %d cmd_id: %u",uPkgSize, m_packet.cmd_id_);
	//返回解出的cmd_id作为msgID，平台收到msgID后，会查找HANDLERMAP，若msgID存在绑定的函数，则调用该函数
	return m_packet.cmd_id_;
}

//no need to auto create
const char * CG4GameProcess::GetCurDateTimeCStr(struct timeval *pstNowTime) {
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

    snprintf(s, sizeof(s)-1, "%02d:%02d:%02d",curr.tm_hour, curr.tm_min, curr.tm_sec);
	
	
    snprintf(sTimeStr,100,"[%s.%.6ld]",s,(long)pstNowTime->tv_usec);

    return sTimeStr;

}


//no need to auto create
int CG4GameProcess::OnGetPlayerTokenRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetPlayerTokenRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetPlayerTokenRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	
	UserInfo *robot = GetUserInfo(dwUin);
	robot->token = std::string(rsp.token());
	
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetPlayerTokenReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetPlayerTokenRsp\n" + debug_str + "</recv>";
	
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());

	return 0;
}

//auto created code start
int CG4GameProcess::OnEntityFightPropChangeReasonNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEntityFightPropChangeReasonNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EntityFightPropChangeReasonNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EntityFightPropChangeReasonNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EntityFightPropChangeReasonNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSetUpAvatarTeamRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSetUpAvatarTeamRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SetUpAvatarTeamRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SetUpAvatarTeamReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SetUpAvatarTeamRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetPlayerFriendListRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetPlayerFriendListRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetPlayerFriendListRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetPlayerFriendListReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetPlayerFriendListRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerPropNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerPropNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerPropNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerPropNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerPropNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnUnfreezeGroupLimitNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnUnfreezeGroupLimitNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::UnfreezeGroupLimitNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_UnfreezeGroupLimitNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " UnfreezeGroupLimitNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnBeginCameraSceneLookNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnBeginCameraSceneLookNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::BeginCameraSceneLookNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_BeginCameraSceneLookNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " BeginCameraSceneLookNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarDataNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarDataNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarDataNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarDataNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnShowMessageNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnShowMessageNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ShowMessageNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ShowMessageNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ShowMessageNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEvtAvatarSitDownNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEvtAvatarSitDownNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EvtAvatarSitDownNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EvtAvatarSitDownNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EvtAvatarSitDownNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnLevelupCityRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnLevelupCityRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::LevelupCityRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_LevelupCityReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " LevelupCityRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerLevelRewardUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerLevelRewardUpdateNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerLevelRewardUpdateNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerLevelRewardUpdateNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerLevelRewardUpdateNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnBargainTerminateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnBargainTerminateNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::BargainTerminateNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_BargainTerminateNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " BargainTerminateNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEvtCreateGadgetNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEvtCreateGadgetNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EvtCreateGadgetNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EvtCreateGadgetNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EvtCreateGadgetNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarEquipChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarEquipChangeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarEquipChangeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarEquipChangeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarEquipChangeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnTowerBuffSelectRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnTowerBuffSelectRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::TowerBuffSelectRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_TowerBuffSelectReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " TowerBuffSelectRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnMaterialDeleteReturnNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnMaterialDeleteReturnNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::MaterialDeleteReturnNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_MaterialDeleteReturnNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " MaterialDeleteReturnNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneForceLockNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneForceLockNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneForceLockNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneForceLockNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneForceLockNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDoGachaRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDoGachaRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DoGachaRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DoGachaReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DoGachaRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonCandidateTeamReplyInviteRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonCandidateTeamReplyInviteRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonCandidateTeamReplyInviteRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonCandidateTeamReplyInviteReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonCandidateTeamReplyInviteRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSyncTeamEntityNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSyncTeamEntityNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SyncTeamEntityNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SyncTeamEntityNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SyncTeamEntityNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnMarkEntityInMinMapNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnMarkEntityInMinMapNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::MarkEntityInMinMapNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_MarkEntityInMinMapNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " MarkEntityInMinMapNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnExecuteGroupTriggerRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnExecuteGroupTriggerRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ExecuteGroupTriggerRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ExecuteGroupTriggerReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ExecuteGroupTriggerRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnForgeStartRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnForgeStartRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ForgeStartRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ForgeStartReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ForgeStartRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetDungeonEntryExploreConditionRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetDungeonEntryExploreConditionRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetDungeonEntryExploreConditionRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetDungeonEntryExploreConditionReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetDungeonEntryExploreConditionRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEvtBeingHitNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEvtBeingHitNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EvtBeingHitNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EvtBeingHitNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EvtBeingHitNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnQuestCreateEntityRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnQuestCreateEntityRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::QuestCreateEntityRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_QuestCreateEntityReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " QuestCreateEntityRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnBuyWorldResinRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnBuyWorldResinRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::BuyWorldResinRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_BuyWorldResinReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " BuyWorldResinRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSetPlayerNameRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSetPlayerNameRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SetPlayerNameRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SetPlayerNameReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SetPlayerNameRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnStoreItemChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnStoreItemChangeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::StoreItemChangeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_StoreItemChangeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " StoreItemChangeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarPropChangeReasonNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarPropChangeReasonNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarPropChangeReasonNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarPropChangeReasonNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarPropChangeReasonNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnTowerFloorRecordChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnTowerFloorRecordChangeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::TowerFloorRecordChangeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_TowerFloorRecordChangeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " TowerFloorRecordChangeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEnterWorldFogAreaNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEnterWorldFogAreaNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EnterWorldFogAreaNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EnterWorldFogAreaNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EnterWorldFogAreaNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSeaLampFlyLampRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSeaLampFlyLampRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SeaLampFlyLampRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SeaLampFlyLampReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SeaLampFlyLampRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnChallengeRecordNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnChallengeRecordNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ChallengeRecordNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ChallengeRecordNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ChallengeRecordNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerLogoutNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerLogoutNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerLogoutNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerLogoutNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerLogoutNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlatformStopRouteNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlatformStopRouteNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlatformStopRouteNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlatformStopRouteNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlatformStopRouteNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSetEntityClientDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSetEntityClientDataNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SetEntityClientDataNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SetEntityClientDataNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SetEntityClientDataNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerQuitDungeonRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerQuitDungeonRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerQuitDungeonRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerQuitDungeonReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerQuitDungeonRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPathfindingEnterSceneRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPathfindingEnterSceneRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PathfindingEnterSceneRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PathfindingEnterSceneReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PathfindingEnterSceneRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnWorldOwnerBlossomScheduleInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnWorldOwnerBlossomScheduleInfoNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::WorldOwnerBlossomScheduleInfoNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_WorldOwnerBlossomScheduleInfoNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " WorldOwnerBlossomScheduleInfoNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetMailItemRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetMailItemRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetMailItemRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetMailItemReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetMailItemRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPushTipsAllDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPushTipsAllDataNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PushTipsAllDataNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PushTipsAllDataNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PushTipsAllDataNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonCandidateTeamLeaveRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonCandidateTeamLeaveRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonCandidateTeamLeaveRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonCandidateTeamLeaveReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonCandidateTeamLeaveRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEnterSceneWeatherAreaNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEnterSceneWeatherAreaNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EnterSceneWeatherAreaNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EnterSceneWeatherAreaNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EnterSceneWeatherAreaNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGMShowObstacleRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGMShowObstacleRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GMShowObstacleRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GMShowObstacleReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GMShowObstacleRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneEntitiesMovesRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneEntitiesMovesRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneEntitiesMovesRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneEntitiesMovesReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneEntitiesMovesRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnWatcherAllDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnWatcherAllDataNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::WatcherAllDataNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_WatcherAllDataNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " WatcherAllDataNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEvtBulletMoveNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEvtBulletMoveNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EvtBulletMoveNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EvtBulletMoveNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EvtBulletMoveNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnReliquaryPromoteRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnReliquaryPromoteRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ReliquaryPromoteRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ReliquaryPromoteReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ReliquaryPromoteRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerInvestigationNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerInvestigationNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerInvestigationNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerInvestigationNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerInvestigationNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnItemAddHintNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnItemAddHintNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ItemAddHintNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ItemAddHintNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ItemAddHintNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnRechargeRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnRechargeRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::RechargeRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_RechargeReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " RechargeRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnBackMyWorldRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnBackMyWorldRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::BackMyWorldRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_BackMyWorldReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " BackMyWorldRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnForgeQueueDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnForgeQueueDataNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ForgeQueueDataNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ForgeQueueDataNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ForgeQueueDataNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnChangeMpTeamAvatarRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnChangeMpTeamAvatarRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ChangeMpTeamAvatarRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ChangeMpTeamAvatarReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ChangeMpTeamAvatarRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnUnlockWorldFogAreaNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnUnlockWorldFogAreaNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::UnlockWorldFogAreaNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_UnlockWorldFogAreaNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " UnlockWorldFogAreaNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnBuyGoodsRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnBuyGoodsRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::BuyGoodsRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_BuyGoodsReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " BuyGoodsRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAddRandTaskInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAddRandTaskInfoNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AddRandTaskInfoNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AddRandTaskInfoNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AddRandTaskInfoNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSpringUseRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSpringUseRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SpringUseRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SpringUseReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SpringUseRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarLifeStateChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarLifeStateChangeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarLifeStateChangeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarLifeStateChangeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarLifeStateChangeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonCandidateTeamChangeAvatarRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonCandidateTeamChangeAvatarRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonCandidateTeamChangeAvatarRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonCandidateTeamChangeAvatarReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonCandidateTeamChangeAvatarRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnCreateMassiveEntityRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnCreateMassiveEntityRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::CreateMassiveEntityRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_CreateMassiveEntityReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " CreateMassiveEntityRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPathfindingPingNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPathfindingPingNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PathfindingPingNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PathfindingPingNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PathfindingPingNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarExpeditionGetRewardRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarExpeditionGetRewardRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarExpeditionGetRewardRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarExpeditionGetRewardReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarExpeditionGetRewardRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarFightPropUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarFightPropUpdateNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarFightPropUpdateNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarFightPropUpdateNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarFightPropUpdateNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetPushTipsRewardRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetPushTipsRewardRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetPushTipsRewardRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetPushTipsRewardReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetPushTipsRewardRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnChooseCurAvatarTeamRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnChooseCurAvatarTeamRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ChooseCurAvatarTeamRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ChooseCurAvatarTeamReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ChooseCurAvatarTeamRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnLogTalkNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnLogTalkNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::LogTalkNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_LogTalkNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " LogTalkNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDoSetPlayerBornDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDoSetPlayerBornDataNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DoSetPlayerBornDataNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DoSetPlayerBornDataNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DoSetPlayerBornDataNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonCandidateTeamPlayerLeaveNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonCandidateTeamPlayerLeaveNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonCandidateTeamPlayerLeaveNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonCandidateTeamPlayerLeaveNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonCandidateTeamPlayerLeaveNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlatformChangeRouteNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlatformChangeRouteNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlatformChangeRouteNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlatformChangeRouteNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlatformChangeRouteNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDailyTaskDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDailyTaskDataNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DailyTaskDataNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DailyTaskDataNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DailyTaskDataNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEvtSetAttackTargetNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEvtSetAttackTargetNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EvtSetAttackTargetNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EvtSetAttackTargetNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EvtSetAttackTargetNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnHitClientTrivialNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnHitClientTrivialNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::HitClientTrivialNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_HitClientTrivialNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " HitClientTrivialNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonDieOptionRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonDieOptionRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonDieOptionRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonDieOptionReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonDieOptionRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnTowerSurrenderRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnTowerSurrenderRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::TowerSurrenderRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_TowerSurrenderReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " TowerSurrenderRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetPlayerSocialDetailRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetPlayerSocialDetailRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetPlayerSocialDetailRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetPlayerSocialDetailReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetPlayerSocialDetailRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneTransToPointRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneTransToPointRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneTransToPointRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneTransToPointReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneTransToPointRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonChallengeFinishNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonChallengeFinishNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonChallengeFinishNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonChallengeFinishNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonChallengeFinishNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnQuestProgressUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnQuestProgressUpdateNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::QuestProgressUpdateNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_QuestProgressUpdateNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " QuestProgressUpdateNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneGetAreaExplorePercentRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneGetAreaExplorePercentRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneGetAreaExplorePercentRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneGetAreaExplorePercentReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneGetAreaExplorePercentRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEntityJumpNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEntityJumpNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EntityJumpNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EntityJumpNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EntityJumpNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSealBattleProgressNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSealBattleProgressNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SealBattleProgressNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SealBattleProgressNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SealBattleProgressNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSignInInfoRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSignInInfoRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SignInInfoRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SignInInfoReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SignInInfoRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnJoinPlayerFailNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnJoinPlayerFailNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::JoinPlayerFailNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_JoinPlayerFailNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " JoinPlayerFailNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnClientScriptEventNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnClientScriptEventNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ClientScriptEventNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ClientScriptEventNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ClientScriptEventNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGivingRecordChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGivingRecordChangeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GivingRecordChangeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GivingRecordChangeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GivingRecordChangeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnUnlockTransPointRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnUnlockTransPointRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::UnlockTransPointRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_UnlockTransPointReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " UnlockTransPointRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnClientAbilityInitBeginNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnClientAbilityInitBeginNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ClientAbilityInitBeginNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ClientAbilityInitBeginNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ClientAbilityInitBeginNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerApplyEnterMpRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerApplyEnterMpRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerApplyEnterMpRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerApplyEnterMpReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerApplyEnterMpRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnServerTimeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnServerTimeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ServerTimeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ServerTimeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ServerTimeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnClientAbilitiesInitFinishCombineNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnClientAbilitiesInitFinishCombineNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ClientAbilitiesInitFinishCombineNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ClientAbilitiesInitFinishCombineNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ClientAbilitiesInitFinishCombineNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnWorldPlayerLocationNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnWorldPlayerLocationNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::WorldPlayerLocationNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_WorldPlayerLocationNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " WorldPlayerLocationNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnTowerAllDataRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnTowerAllDataRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::TowerAllDataRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_TowerAllDataReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " TowerAllDataRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSetPlayerSignatureRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSetPlayerSignatureRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SetPlayerSignatureRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SetPlayerSignatureReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SetPlayerSignatureRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerDataNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerDataNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerDataNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerDataNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonCandidateTeamRefuseNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonCandidateTeamRefuseNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonCandidateTeamRefuseNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonCandidateTeamRefuseNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonCandidateTeamRefuseNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonWayPointNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonWayPointNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonWayPointNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonWayPointNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonWayPointNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerChatNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerChatNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerChatNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerChatNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerChatNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEvtAnimatorStateChangedNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEvtAnimatorStateChangedNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EvtAnimatorStateChangedNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EvtAnimatorStateChangedNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EvtAnimatorStateChangedNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSetOpenStateRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSetOpenStateRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SetOpenStateRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SetOpenStateReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SetOpenStateRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnTakeInvestigationTargetRewardRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnTakeInvestigationTargetRewardRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::TakeInvestigationTargetRewardRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_TakeInvestigationTargetRewardReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " TakeInvestigationTargetRewardRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnWorldPlayerInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnWorldPlayerInfoNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::WorldPlayerInfoNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_WorldPlayerInfoNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " WorldPlayerInfoNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnQuestDestroyEntityRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnQuestDestroyEntityRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::QuestDestroyEntityRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_QuestDestroyEntityReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " QuestDestroyEntityRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnCookDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnCookDataNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::CookDataNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_CookDataNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " CookDataNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnMonsterForceAlertNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnMonsterForceAlertNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::MonsterForceAlertNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_MonsterForceAlertNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " MonsterForceAlertNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAllMarkPointNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAllMarkPointNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AllMarkPointNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AllMarkPointNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AllMarkPointNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnTowerMiddleLevelChangeTeamNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnTowerMiddleLevelChangeTeamNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::TowerMiddleLevelChangeTeamNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_TowerMiddleLevelChangeTeamNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " TowerMiddleLevelChangeTeamNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneKickPlayerNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneKickPlayerNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneKickPlayerNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneKickPlayerNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneKickPlayerNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneEntitiesMoveCombineNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneEntitiesMoveCombineNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneEntitiesMoveCombineNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneEntitiesMoveCombineNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneEntitiesMoveCombineNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnOpenStateChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnOpenStateChangeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::OpenStateChangeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_OpenStateChangeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " OpenStateChangeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnTowerDailyRewardProgressChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnTowerDailyRewardProgressChangeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::TowerDailyRewardProgressChangeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_TowerDailyRewardProgressChangeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " TowerDailyRewardProgressChangeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnBargainOfferPriceRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnBargainOfferPriceRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::BargainOfferPriceRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_BargainOfferPriceReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " BargainOfferPriceRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnTakeInvestigationRewardRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnTakeInvestigationRewardRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::TakeInvestigationRewardRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_TakeInvestigationRewardReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " TakeInvestigationRewardRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnFinishedParentQuestNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnFinishedParentQuestNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::FinishedParentQuestNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_FinishedParentQuestNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " FinishedParentQuestNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnBuyResinRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnBuyResinRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::BuyResinRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_BuyResinReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " BuyResinRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnMonsterAlertChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnMonsterAlertChangeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::MonsterAlertChangeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_MonsterAlertChangeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " MonsterAlertChangeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnResinChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnResinChangeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ResinChangeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ResinChangeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ResinChangeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerPropChangeReasonNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerPropChangeReasonNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerPropChangeReasonNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerPropChangeReasonNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerPropChangeReasonNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarBuffDelNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarBuffDelNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarBuffDelNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarBuffDelNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarBuffDelNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSeaLampTakeContributionRewardRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSeaLampTakeContributionRewardRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SeaLampTakeContributionRewardRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SeaLampTakeContributionRewardReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SeaLampTakeContributionRewardRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSignInInfoOpenNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSignInInfoOpenNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SignInInfoOpenNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SignInInfoOpenNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SignInInfoOpenNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnCutSceneFinishNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnCutSceneFinishNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::CutSceneFinishNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_CutSceneFinishNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " CutSceneFinishNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetCompoundDataRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetCompoundDataRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetCompoundDataRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetCompoundDataReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetCompoundDataRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneDataNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneDataNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneDataNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneDataNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnExitSceneWeatherAreaNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnExitSceneWeatherAreaNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ExitSceneWeatherAreaNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ExitSceneWeatherAreaNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ExitSceneWeatherAreaNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnCutSceneBeginNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnCutSceneBeginNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::CutSceneBeginNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_CutSceneBeginNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " CutSceneBeginNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEvtDestroyGadgetNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEvtDestroyGadgetNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EvtDestroyGadgetNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EvtDestroyGadgetNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EvtDestroyGadgetNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarDieAnimationEndRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarDieAnimationEndRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarDieAnimationEndRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarDieAnimationEndReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarDieAnimationEndRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnClientPauseNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnClientPauseNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ClientPauseNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ClientPauseNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ClientPauseNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGrantRewardNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGrantRewardNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GrantRewardNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GrantRewardNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GrantRewardNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneEntityDisappearNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneEntityDisappearNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneEntityDisappearNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneEntityDisappearNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneEntityDisappearNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonPlayerDieNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonPlayerDieNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonPlayerDieNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonPlayerDieNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonPlayerDieNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneAreaExploreNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneAreaExploreNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneAreaExploreNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneAreaExploreNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneAreaExploreNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarAbilityResetFinishNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarAbilityResetFinishNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarAbilityResetFinishNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarAbilityResetFinishNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarAbilityResetFinishNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnTakeoffEquipRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnTakeoffEquipRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::TakeoffEquipRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_TakeoffEquipReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " TakeoffEquipRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneEntityDrownRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneEntityDrownRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneEntityDrownRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneEntityDrownReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneEntityDrownRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSetPlayerHeadImageRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSetPlayerHeadImageRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SetPlayerHeadImageRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SetPlayerHeadImageReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SetPlayerHeadImageRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnBonusActivityUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnBonusActivityUpdateNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::BonusActivityUpdateNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_BonusActivityUpdateNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " BonusActivityUpdateNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEvtAiSyncSkillCdNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEvtAiSyncSkillCdNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EvtAiSyncSkillCdNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EvtAiSyncSkillCdNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EvtAiSyncSkillCdNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonCandidateTeamDismissNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonCandidateTeamDismissNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonCandidateTeamDismissNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonCandidateTeamDismissNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonCandidateTeamDismissNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnActivityPlayOpenAnimNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnActivityPlayOpenAnimNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ActivityPlayOpenAnimNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ActivityPlayOpenAnimNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ActivityPlayOpenAnimNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnTakeCompoundOutputRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnTakeCompoundOutputRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::TakeCompoundOutputRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_TakeCompoundOutputReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " TakeCompoundOutputRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGMShowNavMeshRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGMShowNavMeshRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GMShowNavMeshRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GMShowNavMeshReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GMShowNavMeshRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEvtAvatarStandUpNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEvtAvatarStandUpNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EvtAvatarStandUpNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EvtAvatarStandUpNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EvtAvatarStandUpNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetInvestigationMonsterRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetInvestigationMonsterRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetInvestigationMonsterRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetInvestigationMonsterReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetInvestigationMonsterRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerStoreNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerStoreNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerStoreNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerStoreNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerStoreNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonEntryToBeExploreNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonEntryToBeExploreNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonEntryToBeExploreNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonEntryToBeExploreNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonEntryToBeExploreNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnBattlePassAllDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnBattlePassAllDataNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::BattlePassAllDataNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_BattlePassAllDataNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " BattlePassAllDataNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEvtRushMoveNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEvtRushMoveNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EvtRushMoveNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EvtRushMoveNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EvtRushMoveNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEnterScenePeerNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEnterScenePeerNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EnterScenePeerNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EnterScenePeerNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EnterScenePeerNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnMaterialDeleteUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnMaterialDeleteUpdateNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::MaterialDeleteUpdateNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_MaterialDeleteUpdateNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " MaterialDeleteUpdateNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEntityFightPropNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEntityFightPropNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EntityFightPropNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EntityFightPropNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EntityFightPropNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnTakeBattlePassRewardRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnTakeBattlePassRewardRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::TakeBattlePassRewardRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_TakeBattlePassRewardReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " TakeBattlePassRewardRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarExpeditionDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarExpeditionDataNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarExpeditionDataNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarExpeditionDataNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarExpeditionDataNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerCookRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerCookRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerCookRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerCookReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerCookRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnWatcherEventTypeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnWatcherEventTypeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::WatcherEventTypeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_WatcherEventTypeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " WatcherEventTypeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonCandidateTeamInviteRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonCandidateTeamInviteRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonCandidateTeamInviteRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonCandidateTeamInviteReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonCandidateTeamInviteRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEvtEntityRenderersChangedNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEvtEntityRenderersChangedNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EvtEntityRenderersChangedNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EvtEntityRenderersChangedNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EvtEntityRenderersChangedNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnWorktopOptionNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnWorktopOptionNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::WorktopOptionNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_WorktopOptionNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " WorktopOptionNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetSignInRewardRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetSignInRewardRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetSignInRewardRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetSignInRewardReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetSignInRewardRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarFetterDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarFetterDataNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarFetterDataNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarFetterDataNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarFetterDataNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSetSceneWeatherAreaRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSetSceneWeatherAreaRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SetSceneWeatherAreaRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SetSceneWeatherAreaReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SetSceneWeatherAreaRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnChangeAvatarRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnChangeAvatarRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ChangeAvatarRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ChangeAvatarReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ChangeAvatarRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAddQuestContentProgressRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAddQuestContentProgressRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AddQuestContentProgressRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AddQuestContentProgressReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AddQuestContentProgressRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnLeaveSceneRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnLeaveSceneRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::LeaveSceneRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_LeaveSceneReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " LeaveSceneRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnScenePointUnlockNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnScenePointUnlockNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ScenePointUnlockNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ScenePointUnlockNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ScenePointUnlockNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnWorldOwnerDailyTaskNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnWorldOwnerDailyTaskNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::WorldOwnerDailyTaskNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_WorldOwnerDailyTaskNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " WorldOwnerDailyTaskNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneEntityAppearNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneEntityAppearNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneEntityAppearNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneEntityAppearNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneEntityAppearNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnWeaponAwakenRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnWeaponAwakenRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::WeaponAwakenRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_WeaponAwakenReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " WeaponAwakenRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarTeamUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarTeamUpdateNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarTeamUpdateNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarTeamUpdateNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarTeamUpdateNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonCandidateTeamCreateRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonCandidateTeamCreateRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonCandidateTeamCreateRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonCandidateTeamCreateReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonCandidateTeamCreateRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnWeaponPromoteRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnWeaponPromoteRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::WeaponPromoteRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_WeaponPromoteReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " WeaponPromoteRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneKickPlayerRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneKickPlayerRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneKickPlayerRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneKickPlayerReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneKickPlayerRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDestroyMassiveEntityNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDestroyMassiveEntityNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DestroyMassiveEntityNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DestroyMassiveEntityNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DestroyMassiveEntityNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPostEnterSceneRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPostEnterSceneRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PostEnterSceneRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PostEnterSceneReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PostEnterSceneRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetShopmallDataRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetShopmallDataRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetShopmallDataRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetShopmallDataReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetShopmallDataRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEnterSceneReadyRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEnterSceneReadyRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EnterSceneReadyRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EnterSceneReadyReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EnterSceneReadyRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneTeamUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneTeamUpdateNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneTeamUpdateNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneTeamUpdateNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneTeamUpdateNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnCookGradeDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnCookGradeDataNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::CookGradeDataNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_CookGradeDataNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " CookGradeDataNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnRefreshBackgroundAvatarRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnRefreshBackgroundAvatarRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::RefreshBackgroundAvatarRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_RefreshBackgroundAvatarReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " RefreshBackgroundAvatarRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnScenePlayerSoundNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnScenePlayerSoundNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ScenePlayerSoundNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ScenePlayerSoundNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ScenePlayerSoundNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEvtBulletDeactiveNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEvtBulletDeactiveNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EvtBulletDeactiveNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EvtBulletDeactiveNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EvtBulletDeactiveNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonWayPointActivateRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonWayPointActivateRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonWayPointActivateRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonWayPointActivateReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonWayPointActivateRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEnterTransPointRegionNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEnterTransPointRegionNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EnterTransPointRegionNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EnterTransPointRegionNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EnterTransPointRegionNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerCookArgsRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerCookArgsRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerCookArgsRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerCookArgsReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerCookArgsRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnBlossomChestInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnBlossomChestInfoNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::BlossomChestInfoNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_BlossomChestInfoNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " BlossomChestInfoNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerApplyEnterMpResultRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerApplyEnterMpResultRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerApplyEnterMpResultRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerApplyEnterMpResultReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerApplyEnterMpResultRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnBattlePassCurScheduleUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnBattlePassCurScheduleUpdateNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::BattlePassCurScheduleUpdateNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_BattlePassCurScheduleUpdateNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " BattlePassCurScheduleUpdateNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnClientNewMailNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnClientNewMailNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ClientNewMailNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ClientNewMailNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ClientNewMailNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEvtEntityStartDieEndNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEvtEntityStartDieEndNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EvtEntityStartDieEndNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EvtEntityStartDieEndNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EvtEntityStartDieEndNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnQuestDelNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnQuestDelNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::QuestDelNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_QuestDelNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " QuestDelNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnItemCdGroupTimeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnItemCdGroupTimeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ItemCdGroupTimeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ItemCdGroupTimeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ItemCdGroupTimeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnBattlePassMissionUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnBattlePassMissionUpdateNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::BattlePassMissionUpdateNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_BattlePassMissionUpdateNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " BattlePassMissionUpdateNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerLoginRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerLoginRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerLoginRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerLoginReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerLoginRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnCreateMassiveEntityNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnCreateMassiveEntityNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::CreateMassiveEntityNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_CreateMassiveEntityNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " CreateMassiveEntityNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnCombineRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnCombineRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::CombineRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_CombineReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " CombineRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSealBattleBeginNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSealBattleBeginNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SealBattleBeginNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SealBattleBeginNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SealBattleBeginNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAllSeenMonsterNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAllSeenMonsterNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AllSeenMonsterNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AllSeenMonsterNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AllSeenMonsterNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnWeaponUpgradeRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnWeaponUpgradeRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::WeaponUpgradeRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_WeaponUpgradeReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " WeaponUpgradeRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAnimatorForceSetAirMoveNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAnimatorForceSetAirMoveNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AnimatorForceSetAirMoveNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AnimatorForceSetAirMoveNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AnimatorForceSetAirMoveNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarUnlockTalentNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarUnlockTalentNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarUnlockTalentNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarUnlockTalentNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarUnlockTalentNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneCreateEntityRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneCreateEntityRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneCreateEntityRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneCreateEntityReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneCreateEntityRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnWatcherEventNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnWatcherEventNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::WatcherEventNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_WatcherEventNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " WatcherEventNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnNpcTalkRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnNpcTalkRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::NpcTalkRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_NpcTalkReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " NpcTalkRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAbilityInvocationsNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAbilityInvocationsNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AbilityInvocationsNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AbilityInvocationsNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AbilityInvocationsNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlatformRouteStateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlatformRouteStateNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlatformRouteStateNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlatformRouteStateNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlatformRouteStateNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEntityFightPropUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEntityFightPropUpdateNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EntityFightPropUpdateNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EntityFightPropUpdateNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EntityFightPropUpdateNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerLuaShellNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerLuaShellNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerLuaShellNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerLuaShellNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerLuaShellNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnQuestDestroyNpcRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnQuestDestroyNpcRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::QuestDestroyNpcRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_QuestDestroyNpcReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " QuestDestroyNpcRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneRouteChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneRouteChangeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneRouteChangeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneRouteChangeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneRouteChangeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEntityMoveRoomNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEntityMoveRoomNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EntityMoveRoomNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EntityMoveRoomNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EntityMoveRoomNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnTowerLevelEndNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnTowerLevelEndNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::TowerLevelEndNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_TowerLevelEndNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " TowerLevelEndNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerEnterDungeonRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerEnterDungeonRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerEnterDungeonRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerEnterDungeonReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerEnterDungeonRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneDestroyEntityRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneDestroyEntityRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneDestroyEntityRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneDestroyEntityReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneDestroyEntityRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnLifeStateChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnLifeStateChangeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::LifeStateChangeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_LifeStateChangeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " LifeStateChangeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnRemoveRandTaskInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnRemoveRandTaskInfoNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::RemoveRandTaskInfoNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_RemoveRandTaskInfoNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " RemoveRandTaskInfoNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnActivityScheduleInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnActivityScheduleInfoNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ActivityScheduleInfoNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ActivityScheduleInfoNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ActivityScheduleInfoNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnServerBuffChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnServerBuffChangeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ServerBuffChangeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ServerBuffChangeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ServerBuffChangeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnReadMailNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnReadMailNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ReadMailNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ReadMailNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ReadMailNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnWindSeedClientNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnWindSeedClientNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::WindSeedClientNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_WindSeedClientNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " WindSeedClientNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEvtDoSkillSuccNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEvtDoSkillSuccNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EvtDoSkillSuccNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EvtDoSkillSuccNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EvtDoSkillSuccNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerApplyEnterMpResultNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerApplyEnterMpResultNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerApplyEnterMpResultNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerApplyEnterMpResultNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerApplyEnterMpResultNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerChatCDNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerChatCDNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerChatCDNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerChatCDNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerChatCDNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonCandidateTeamInviteNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonCandidateTeamInviteNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonCandidateTeamInviteNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonCandidateTeamInviteNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonCandidateTeamInviteNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnUnmarkEntityInMinMapNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnUnmarkEntityInMinMapNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::UnmarkEntityInMinMapNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_UnmarkEntityInMinMapNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " UnmarkEntityInMinMapNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnCanUseSkillNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnCanUseSkillNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::CanUseSkillNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_CanUseSkillNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " CanUseSkillNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetAuthkeyRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetAuthkeyRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetAuthkeyRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetAuthkeyReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetAuthkeyRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnChangeTeamNameRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnChangeTeamNameRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ChangeTeamNameRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ChangeTeamNameReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ChangeTeamNameRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonCandidateTeamSetReadyRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonCandidateTeamSetReadyRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonCandidateTeamSetReadyRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonCandidateTeamSetReadyReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonCandidateTeamSetReadyRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnServerAnnounceNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnServerAnnounceNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ServerAnnounceNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ServerAnnounceNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ServerAnnounceNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarExpeditionStartRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarExpeditionStartRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarExpeditionStartRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarExpeditionStartReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarExpeditionStartRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnTowerLevelStarCondNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnTowerLevelStarCondNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::TowerLevelStarCondNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_TowerLevelStarCondNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " TowerLevelStarCondNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEvtAvatarEnterFocusNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEvtAvatarEnterFocusNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EvtAvatarEnterFocusNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EvtAvatarEnterFocusNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EvtAvatarEnterFocusNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnCutSceneEndNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnCutSceneEndNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::CutSceneEndNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_CutSceneEndNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " CutSceneEndNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonFollowNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonFollowNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonFollowNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonFollowNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonFollowNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPushTipsChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPushTipsChangeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PushTipsChangeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PushTipsChangeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PushTipsChangeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarAddNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarAddNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarAddNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarAddNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarAddNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnWatcherChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnWatcherChangeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::WatcherChangeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_WatcherChangeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " WatcherChangeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarSkillMaxChargeCountNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarSkillMaxChargeCountNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarSkillMaxChargeCountNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarSkillMaxChargeCountNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarSkillMaxChargeCountNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetBlossomBriefInfoListRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetBlossomBriefInfoListRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetBlossomBriefInfoListRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetBlossomBriefInfoListReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetBlossomBriefInfoListRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetActivityScheduleRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetActivityScheduleRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetActivityScheduleRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetActivityScheduleReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetActivityScheduleRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEvtBulletHitNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEvtBulletHitNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EvtBulletHitNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EvtBulletHitNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EvtBulletHitNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEvtAiSyncCombatThreatInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEvtAiSyncCombatThreatInfoNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EvtAiSyncCombatThreatInfoNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EvtAiSyncCombatThreatInfoNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EvtAiSyncCombatThreatInfoNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnWorldOwnerBlossomBriefInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnWorldOwnerBlossomBriefInfoNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::WorldOwnerBlossomBriefInfoNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_WorldOwnerBlossomBriefInfoNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " WorldOwnerBlossomBriefInfoNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPushTipsReadFinishRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPushTipsReadFinishRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PushTipsReadFinishRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PushTipsReadFinishReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PushTipsReadFinishRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnOrderFinishNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnOrderFinishNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::OrderFinishNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_OrderFinishNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " OrderFinishNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnCombatInvocationsNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnCombatInvocationsNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::CombatInvocationsNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_CombatInvocationsNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " CombatInvocationsNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnOpenStateUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnOpenStateUpdateNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::OpenStateUpdateNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_OpenStateUpdateNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " OpenStateUpdateNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnWorldPlayerDieNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnWorldPlayerDieNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::WorldPlayerDieNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_WorldPlayerDieNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " WorldPlayerDieNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDealAddFriendRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDealAddFriendRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DealAddFriendRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DealAddFriendReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DealAddFriendRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarEnterElementViewNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarEnterElementViewNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarEnterElementViewNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarEnterElementViewNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarEnterElementViewNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarSkillChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarSkillChangeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarSkillChangeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarSkillChangeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarSkillChangeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEntityPropNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEntityPropNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EntityPropNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EntityPropNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EntityPropNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonPlayerDieRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonPlayerDieRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonPlayerDieRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonPlayerDieReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonPlayerDieRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnFocusAvatarRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnFocusAvatarRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::FocusAvatarRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_FocusAvatarReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " FocusAvatarRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDropItemRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDropItemRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DropItemRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DropItemReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DropItemRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnBuyShopmallGoodsRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnBuyShopmallGoodsRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::BuyShopmallGoodsRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_BuyShopmallGoodsReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " BuyShopmallGoodsRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAddSeenMonsterNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAddSeenMonsterNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AddSeenMonsterNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AddSeenMonsterNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AddSeenMonsterNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarFightPropNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarFightPropNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarFightPropNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarFightPropNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarFightPropNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerInvestigationAllInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerInvestigationAllInfoNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerInvestigationAllInfoNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerInvestigationAllInfoNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerInvestigationAllInfoNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnTowerEnterLevelRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnTowerEnterLevelRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::TowerEnterLevelRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_TowerEnterLevelReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " TowerEnterLevelRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnStoreWeightLimitNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnStoreWeightLimitNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::StoreWeightLimitNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_StoreWeightLimitNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " StoreWeightLimitNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDailyTaskProgressNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDailyTaskProgressNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DailyTaskProgressNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DailyTaskProgressNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DailyTaskProgressNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarAbilityResetNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarAbilityResetNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarAbilityResetNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarAbilityResetNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarAbilityResetNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerEnterSceneNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerEnterSceneNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerEnterSceneNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerEnterSceneNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerEnterSceneNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerInvestigationTargetNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerInvestigationTargetNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerInvestigationTargetNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerInvestigationTargetNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerInvestigationTargetNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSelectWorktopOptionRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSelectWorktopOptionRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SelectWorktopOptionRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SelectWorktopOptionReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SelectWorktopOptionRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnTakePlayerLevelRewardRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnTakePlayerLevelRewardRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::TakePlayerLevelRewardRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_TakePlayerLevelRewardReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " TakePlayerLevelRewardRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnMarkNewNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnMarkNewNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::MarkNewNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_MarkNewNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " MarkNewNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetPlayerMpModeAvailabilityRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetPlayerMpModeAvailabilityRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetPlayerMpModeAvailabilityRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetPlayerMpModeAvailabilityReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetPlayerMpModeAvailabilityRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnChallengeDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnChallengeDataNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ChallengeDataNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ChallengeDataNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ChallengeDataNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonShowReminderNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonShowReminderNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonShowReminderNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonShowReminderNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonShowReminderNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneAvatarStaminaStepRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneAvatarStaminaStepRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneAvatarStaminaStepRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneAvatarStaminaStepReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneAvatarStaminaStepRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnClientTriggerEventNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnClientTriggerEventNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ClientTriggerEventNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ClientTriggerEventNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ClientTriggerEventNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGivingRecordNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGivingRecordNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GivingRecordNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GivingRecordNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GivingRecordNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnProudSkillChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnProudSkillChangeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ProudSkillChangeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ProudSkillChangeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ProudSkillChangeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnQuestUpdateQuestVarNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnQuestUpdateQuestVarNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::QuestUpdateQuestVarNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_QuestUpdateQuestVarNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " QuestUpdateQuestVarNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetGachaInfoRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetGachaInfoRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetGachaInfoRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetGachaInfoReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetGachaInfoRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonGetStatueDropRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonGetStatueDropRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonGetStatueDropRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonGetStatueDropReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonGetStatueDropRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnBattlePassMissionDelNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnBattlePassMissionDelNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::BattlePassMissionDelNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_BattlePassMissionDelNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " BattlePassMissionDelNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnHostPlayerNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnHostPlayerNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::HostPlayerNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_HostPlayerNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " HostPlayerNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarSkillInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarSkillInfoNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarSkillInfoNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarSkillInfoNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarSkillInfoNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerCompoundMaterialRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerCompoundMaterialRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerCompoundMaterialRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerCompoundMaterialReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerCompoundMaterialRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnWorldResinChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnWorldResinChangeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::WorldResinChangeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_WorldResinChangeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " WorldResinChangeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnScenePlayerLocationNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnScenePlayerLocationNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ScenePlayerLocationNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ScenePlayerLocationNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ScenePlayerLocationNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarDelNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarDelNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarDelNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarDelNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarDelNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnWorldDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnWorldDataNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::WorldDataNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_WorldDataNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " WorldDataNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnRobotPushPlayerDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnRobotPushPlayerDataNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::RobotPushPlayerDataNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_RobotPushPlayerDataNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " RobotPushPlayerDataNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnTowerCurLevelRecordChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnTowerCurLevelRecordChangeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::TowerCurLevelRecordChangeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_TowerCurLevelRecordChangeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " TowerCurLevelRecordChangeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonSlipRevivePointActivateRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonSlipRevivePointActivateRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonSlipRevivePointActivateRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonSlipRevivePointActivateReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonSlipRevivePointActivateRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnUnlockAvatarTalentRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnUnlockAvatarTalentRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::UnlockAvatarTalentRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_UnlockAvatarTalentReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " UnlockAvatarTalentRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarUpgradeRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarUpgradeRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarUpgradeRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarUpgradeReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarUpgradeRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnQuestListNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnQuestListNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::QuestListNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_QuestListNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " QuestListNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneAreaUnlockNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneAreaUnlockNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneAreaUnlockNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneAreaUnlockNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneAreaUnlockNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetAllMailRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetAllMailRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetAllMailRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetAllMailReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetAllMailRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDropSubfieldRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDropSubfieldRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DropSubfieldRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DropSubfieldReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DropSubfieldRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnBargainStartNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnBargainStartNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::BargainStartNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_BargainStartNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " BargainStartNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnForgeQueueManipulateRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnForgeQueueManipulateRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ForgeQueueManipulateRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ForgeQueueManipulateReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ForgeQueueManipulateRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnUseItemRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnUseItemRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::UseItemRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_UseItemReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " UseItemRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnObstacleModifyNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnObstacleModifyNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ObstacleModifyNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ObstacleModifyNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ObstacleModifyNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnItemGivingRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnItemGivingRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ItemGivingRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ItemGivingReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ItemGivingRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnMarkMapRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnMarkMapRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::MarkMapRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_MarkMapReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " MarkMapRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneTeamMPDisplayCurAvatarNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneTeamMPDisplayCurAvatarNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneTeamMPDisplayCurAvatarNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneTeamMPDisplayCurAvatarNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneTeamMPDisplayCurAvatarNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonChallengeBeginNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonChallengeBeginNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonChallengeBeginNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonChallengeBeginNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonChallengeBeginNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPersonalSceneJumpRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPersonalSceneJumpRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PersonalSceneJumpRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PersonalSceneJumpReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PersonalSceneJumpRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonCandidateTeamInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonCandidateTeamInfoNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonCandidateTeamInfoNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonCandidateTeamInfoNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonCandidateTeamInfoNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEndCameraSceneLookNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEndCameraSceneLookNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EndCameraSceneLookNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EndCameraSceneLookNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EndCameraSceneLookNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnTriggerCreateGadgetToEquipPartNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnTriggerCreateGadgetToEquipPartNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::TriggerCreateGadgetToEquipPartNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_TriggerCreateGadgetToEquipPartNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " TriggerCreateGadgetToEquipPartNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarExpeditionAllDataRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarExpeditionAllDataRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarExpeditionAllDataRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarExpeditionAllDataReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarExpeditionAllDataRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneEntityMoveNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneEntityMoveNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneEntityMoveNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneEntityMoveNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneEntityMoveNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnBonusActivityInfoRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnBonusActivityInfoRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::BonusActivityInfoRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_BonusActivityInfoReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " BonusActivityInfoRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnWearEquipRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnWearEquipRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::WearEquipRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_WearEquipReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " WearEquipRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnExecuteGadgetLuaRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnExecuteGadgetLuaRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ExecuteGadgetLuaRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ExecuteGadgetLuaReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ExecuteGadgetLuaRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnQuestListUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnQuestListUpdateNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::QuestListUpdateNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_QuestListUpdateNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " QuestListUpdateNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarExpeditionCallBackRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarExpeditionCallBackRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarExpeditionCallBackRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarExpeditionCallBackReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarExpeditionCallBackRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneAreaWeatherNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneAreaWeatherNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneAreaWeatherNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneAreaWeatherNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneAreaWeatherNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSetPlayerBornDataRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSetPlayerBornDataRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SetPlayerBornDataRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SetPlayerBornDataReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SetPlayerBornDataRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnCookRecipeDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnCookRecipeDataNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::CookRecipeDataNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_CookRecipeDataNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " CookRecipeDataNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarSkillUpgradeRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarSkillUpgradeRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarSkillUpgradeRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarSkillUpgradeReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarSkillUpgradeRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerApplyEnterMpNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerApplyEnterMpNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerApplyEnterMpNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerApplyEnterMpNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerApplyEnterMpNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnBonusActivityAllDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnBonusActivityAllDataNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::BonusActivityAllDataNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_BonusActivityAllDataNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " BonusActivityAllDataNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerGameTimeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerGameTimeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerGameTimeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerGameTimeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerGameTimeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEvtAvatarExitFocusNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEvtAvatarExitFocusNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EvtAvatarExitFocusNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EvtAvatarExitFocusNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EvtAvatarExitFocusNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEnterSceneDoneRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEnterSceneDoneRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EnterSceneDoneRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EnterSceneDoneReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EnterSceneDoneRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnClientTransmitRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnClientTransmitRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ClientTransmitRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ClientTransmitReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ClientTransmitRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnBigTalentPointConvertRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnBigTalentPointConvertRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::BigTalentPointConvertRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_BigTalentPointConvertReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " BigTalentPointConvertRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneWeatherForcastRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneWeatherForcastRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneWeatherForcastRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneWeatherForcastReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneWeatherForcastRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnTakeMaterialDeleteReturnRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnTakeMaterialDeleteReturnRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::TakeMaterialDeleteReturnRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_TakeMaterialDeleteReturnReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " TakeMaterialDeleteReturnRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetOnlinePlayerListRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetOnlinePlayerListRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetOnlinePlayerListRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetOnlinePlayerListReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetOnlinePlayerListRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneEntityMoveRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneEntityMoveRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneEntityMoveRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneEntityMoveReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneEntityMoveRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnLogCutsceneNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnLogCutsceneNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::LogCutsceneNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_LogCutsceneNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " LogCutsceneNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnServerAnnounceRevokeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnServerAnnounceRevokeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ServerAnnounceRevokeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ServerAnnounceRevokeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ServerAnnounceRevokeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonEntryInfoRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonEntryInfoRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonEntryInfoRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonEntryInfoReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonEntryInfoRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEnterWorldAreaRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEnterWorldAreaRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EnterWorldAreaRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EnterWorldAreaReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EnterWorldAreaRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDelMailRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDelMailRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DelMailRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DelMailReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DelMailRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAskAddFriendRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAskAddFriendRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AskAddFriendRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AskAddFriendReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AskAddFriendRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerQuitFromMpNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerQuitFromMpNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerQuitFromMpNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerQuitFromMpNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerQuitFromMpNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGmTalkRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGmTalkRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GmTalkRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GmTalkReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GmTalkRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneForceUnlockNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneForceUnlockNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneForceUnlockNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneForceUnlockNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneForceUnlockNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSeaLampContributeItemRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSeaLampContributeItemRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SeaLampContributeItemRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SeaLampContributeItemReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SeaLampContributeItemRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerPreEnterMpNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerPreEnterMpNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerPreEnterMpNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerPreEnterMpNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerPreEnterMpNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSeeMonsterRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSeeMonsterRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SeeMonsterRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SeeMonsterReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SeeMonsterRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnServerLogNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnServerLogNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ServerLogNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ServerLogNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ServerLogNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarPropNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarPropNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarPropNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarPropNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarPropNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetShopmallShopDataRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetShopmallShopDataRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetShopmallShopDataRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetShopmallShopDataReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetShopmallShopDataRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSetPlayerPropRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSetPlayerPropRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SetPlayerPropRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SetPlayerPropReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SetPlayerPropRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonCandidateTeamKickRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonCandidateTeamKickRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonCandidateTeamKickRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonCandidateTeamKickReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonCandidateTeamKickRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnMassiveEntityStateChangedNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnMassiveEntityStateChangedNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::MassiveEntityStateChangedNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_MassiveEntityStateChangedNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " MassiveEntityStateChangedNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerSetLanguageRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerSetLanguageRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerSetLanguageRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerSetLanguageReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerSetLanguageRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnFinishedParentQuestUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnFinishedParentQuestUpdateNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::FinishedParentQuestUpdateNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_FinishedParentQuestUpdateNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " FinishedParentQuestUpdateNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnTowerGetFloorStarRewardRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnTowerGetFloorStarRewardRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::TowerGetFloorStarRewardRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_TowerGetFloorStarRewardReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " TowerGetFloorStarRewardRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonSettleNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonSettleNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonSettleNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonSettleNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonSettleNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEntityAuthorityChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEntityAuthorityChangeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EntityAuthorityChangeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EntityAuthorityChangeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EntityAuthorityChangeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSignInAllDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSignInAllDataNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SignInAllDataNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SignInAllDataNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SignInAllDataNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerPropChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerPropChangeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerPropChangeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerPropChangeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerPropChangeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPingRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPingRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PingRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PingReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PingRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnStoreItemDelNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnStoreItemDelNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::StoreItemDelNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_StoreItemDelNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " StoreItemDelNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnTakeBattlePassMissionPointRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnTakeBattlePassMissionPointRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::TakeBattlePassMissionPointRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_TakeBattlePassMissionPointReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " TakeBattlePassMissionPointRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEntityForceSyncRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEntityForceSyncRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EntityForceSyncRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EntityForceSyncReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EntityForceSyncRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetScenePointRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetScenePointRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetScenePointRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetScenePointReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetScenePointRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnElementReactionLogNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnElementReactionLogNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ElementReactionLogNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ElementReactionLogNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ElementReactionLogNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSeaLampTakePhaseRewardRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSeaLampTakePhaseRewardRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SeaLampTakePhaseRewardRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SeaLampTakePhaseRewardReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SeaLampTakePhaseRewardRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGadgetInteractRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGadgetInteractRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GadgetInteractRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GadgetInteractReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GadgetInteractRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnServerDisconnectClientNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnServerDisconnectClientNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ServerDisconnectClientNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ServerDisconnectClientNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ServerDisconnectClientNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneTimeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneTimeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneTimeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneTimeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneTimeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnScenePlayerInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnScenePlayerInfoNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ScenePlayerInfoNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ScenePlayerInfoNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ScenePlayerInfoNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnKeepAliveNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnKeepAliveNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::KeepAliveNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_KeepAliveNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " KeepAliveNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEvtBeingHitsCombineNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEvtBeingHitsCombineNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EvtBeingHitsCombineNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EvtBeingHitsCombineNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EvtBeingHitsCombineNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnClientAbilityInitFinishNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnClientAbilityInitFinishNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ClientAbilityInitFinishNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ClientAbilityInitFinishNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ClientAbilityInitFinishNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarBuffAddNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarBuffAddNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarBuffAddNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarBuffAddNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarBuffAddNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDungeonDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDungeonDataNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DungeonDataNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DungeonDataNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DungeonDataNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnExitTransPointRegionNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnExitTransPointRegionNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ExitTransPointRegionNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ExitTransPointRegionNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ExitTransPointRegionNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarPromoteRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarPromoteRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarPromoteRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarPromoteReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarPromoteRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnClientFpsStatusNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnClientFpsStatusNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ClientFpsStatusNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ClientFpsStatusNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ClientFpsStatusNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerChatRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerChatRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerChatRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerChatReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerChatRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnQuestUpdateQuestVarRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnQuestUpdateQuestVarRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::QuestUpdateQuestVarRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_QuestUpdateQuestVarReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " QuestUpdateQuestVarRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnTowerTeamSelectRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnTowerTeamSelectRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::TowerTeamSelectRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_TowerTeamSelectReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " TowerTeamSelectRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnMonsterSummonTagNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnMonsterSummonTagNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::MonsterSummonTagNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_MonsterSummonTagNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " MonsterSummonTagNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnActivityInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnActivityInfoNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ActivityInfoNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ActivityInfoNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ActivityInfoNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSetPlayerBirthdayRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSetPlayerBirthdayRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SetPlayerBirthdayRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SetPlayerBirthdayReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SetPlayerBirthdayRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEvtCostStaminaNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEvtCostStaminaNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EvtCostStaminaNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EvtCostStaminaNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EvtCostStaminaNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnChatHistoryNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnChatHistoryNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ChatHistoryNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ChatHistoryNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ChatHistoryNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnQueryPathRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnQueryPathRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::QueryPathRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_QueryPathReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " QueryPathRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerLogoutRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerLogoutRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerLogoutRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerLogoutReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerLogoutRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSealBattleEndNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSealBattleEndNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SealBattleEndNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SealBattleEndNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SealBattleEndNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnChangeGameTimeRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnChangeGameTimeRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ChangeGameTimeRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ChangeGameTimeReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ChangeGameTimeRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnTowerBriefDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnTowerBriefDataNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::TowerBriefDataNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_TowerBriefDataNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " TowerBriefDataNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnProudSkillExtraLevelNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnProudSkillExtraLevelNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ProudSkillExtraLevelNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ProudSkillExtraLevelNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ProudSkillExtraLevelNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerEnterSceneInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerEnterSceneInfoNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerEnterSceneInfoNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerEnterSceneInfoNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerEnterSceneInfoNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAbilityInvocationFixedNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAbilityInvocationFixedNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AbilityInvocationFixedNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AbilityInvocationFixedNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AbilityInvocationFixedNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnClientReconnectNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnClientReconnectNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ClientReconnectNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ClientReconnectNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ClientReconnectNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarSkillDepotChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarSkillDepotChangeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarSkillDepotChangeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarSkillDepotChangeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarSkillDepotChangeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetSceneAreaRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetSceneAreaRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetSceneAreaRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetSceneAreaReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetSceneAreaRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEvtAnimatorParameterNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEvtAnimatorParameterNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EvtAnimatorParameterNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EvtAnimatorParameterNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EvtAnimatorParameterNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnLoadActivityTerrainNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnLoadActivityTerrainNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::LoadActivityTerrainNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_LoadActivityTerrainNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " LoadActivityTerrainNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnReliquaryUpgradeRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnReliquaryUpgradeRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ReliquaryUpgradeRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ReliquaryUpgradeReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ReliquaryUpgradeRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDeleteFriendRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDeleteFriendRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DeleteFriendRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DeleteFriendReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DeleteFriendRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnProudSkillUpgradeRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnProudSkillUpgradeRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ProudSkillUpgradeRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ProudSkillUpgradeReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ProudSkillUpgradeRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnSceneInitFinishRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnSceneInitFinishRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::SceneInitFinishRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_SceneInitFinishReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " SceneInitFinishRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGadgetStateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGadgetStateNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GadgetStateNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GadgetStateNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GadgetStateNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnLockWorldFogAreaNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnLockWorldFogAreaNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::LockWorldFogAreaNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_LockWorldFogAreaNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " LockWorldFogAreaNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEvtFaceToDirNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEvtFaceToDirNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EvtFaceToDirNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EvtFaceToDirNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EvtFaceToDirNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetQuestTalkHistoryRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetQuestTalkHistoryRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetQuestTalkHistoryRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetQuestTalkHistoryReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetQuestTalkHistoryRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarCardChangeRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarCardChangeRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarCardChangeRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarCardChangeReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarCardChangeRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlatformStartRouteNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlatformStartRouteNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlatformStartRouteNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlatformStartRouteNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlatformStartRouteNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnBlossomBriefInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnBlossomBriefInfoNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::BlossomBriefInfoNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_BlossomBriefInfoNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " BlossomBriefInfoNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetShopRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetShopRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetShopRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetShopReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetShopRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDailyTaskScoreRewardNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDailyTaskScoreRewardNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DailyTaskScoreRewardNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DailyTaskScoreRewardNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DailyTaskScoreRewardNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetDailyDungeonEntryInfoRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetDailyDungeonEntryInfoRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetDailyDungeonEntryInfoRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetDailyDungeonEntryInfoReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetDailyDungeonEntryInfoRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAvatarChangeElementTypeRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAvatarChangeElementTypeRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AvatarChangeElementTypeRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AvatarChangeElementTypeReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AvatarChangeElementTypeRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetSceneNpcPositionRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetSceneNpcPositionRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetSceneNpcPositionRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetSceneNpcPositionReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetSceneNpcPositionRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerRandomCookRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerRandomCookRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerRandomCookRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerRandomCookReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerRandomCookRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnForgeGetQueueDataRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnForgeGetQueueDataRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ForgeGetQueueDataRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ForgeGetQueueDataReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ForgeGetQueueDataRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnMailChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnMailChangeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::MailChangeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_MailChangeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " MailChangeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEvtFaceToEntityNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEvtFaceToEntityNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EvtFaceToEntityNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EvtFaceToEntityNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EvtFaceToEntityNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnChapterStateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnChapterStateNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ChapterStateNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ChapterStateNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ChapterStateNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnWorldPlayerReviveRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnWorldPlayerReviveRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::WorldPlayerReviveRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_WorldPlayerReviveReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " WorldPlayerReviveRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnBossChestActivateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnBossChestActivateNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::BossChestActivateNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_BossChestActivateNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " BossChestActivateNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnJoinPlayerSceneRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnJoinPlayerSceneRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::JoinPlayerSceneRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_JoinPlayerSceneReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " JoinPlayerSceneRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnEvtAvatarUpdateFocusNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnEvtAvatarUpdateFocusNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::EvtAvatarUpdateFocusNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_EvtAvatarUpdateFocusNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " EvtAvatarUpdateFocusNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnClientReportNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnClientReportNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::ClientReportNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_ClientReportNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " ClientReportNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerTimeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerTimeNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerTimeNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerTimeNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerTimeNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnAbilityInvocationFailNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnAbilityInvocationFailNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::AbilityInvocationFailNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_AbilityInvocationFailNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " AbilityInvocationFailNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDataResVersionNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDataResVersionNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DataResVersionNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DataResVersionNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DataResVersionNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnPlayerSetPauseRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnPlayerSetPauseRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::PlayerSetPauseRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_PlayerSetPauseReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " PlayerSetPauseRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDelTeamEntityNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDelTeamEntityNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DelTeamEntityNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DelTeamEntityNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DelTeamEntityNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetActivityInfoRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetActivityInfoRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetActivityInfoRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetActivityInfoReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetActivityInfoRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnGetBonusActivityRewardRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnGetBonusActivityRewardRsp");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::GetBonusActivityRewardRsp rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_GetBonusActivityRewardReq, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " GetBonusActivityRewardRsp\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnDropHintNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnDropHintNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::DropHintNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_DropHintNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " DropHintNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

int CG4GameProcess::OnCompoundDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode)
{
	m_poFacadePlatform->TestLog(dwUin, "OnCompoundDataNotify");

	m_packet.parseFromArray((char *)pPkg, uPkgSize);

	proto::CompoundDataNotify rsp;
	rsp.ParseFromArray(m_packet.proto_str_.c_str(), m_packet.proto_str_.length());
	m_poFacadePlatform->SetRobotAttr(dwUin, TRANS_CompoundDataNotify, TRANS_DEAL_SUCCESS);

	string debug_str;
	google::protobuf::util::MessageToJsonString(rsp, &debug_str,option);
	debug_str = "\n<recv>\n" + string(GetCurDateTimeCStr(NULL)) + " CompoundDataNotify\n" + debug_str + "</recv>"; 
	m_poFacadePlatform->TestLog(dwUin, "%s", debug_str.c_str());
	return 0;
}

