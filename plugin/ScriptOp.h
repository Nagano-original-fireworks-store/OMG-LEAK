#ifndef _GAME_SCRIPT_OP_H_
#define _GAME_SCRIPT_OP_H_
#include "scriptop_t.h"
#include "Trans.h"
#include <time.h>
#include <google/protobuf/service.h>
#include <google/protobuf/util/json_util.h>
//#include "packet_head.pb.h"
//#include "player.pb.h"
#include "Hk4eProto.h"

#include "UserInfo.h"
#include <fstream> 


using namespace std;


/*
发包处理类，需实现以下功能

1. 将lua中的DoCommand发包传入的事务名称字符串关联到具体的发包函数，通过ADD_OPMAP宏实现
2. 填充pParam->m_pPkgBuf为最终发包buffer
3. 填充pParam->m_nBufLen为最终发包长度

只需满足上述需求，类实现可任意，为简单起见，提供如下模板
*/
class CG4GameScriptOp: public TScriptOp<CG4GameScriptOp>
{
public:
	//构造和析构
    CG4GameScriptOp();
    ~CG4GameScriptOp();
private:
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
    int SendPkg(unsigned int dwUin, int iMsgID, STScriptOpParam *pParam, int nPkgBufLen);
	void PackProtobuf(unsigned int dwUin, unsigned short wCmdID, google::protobuf::Message &req, string &data_pb);
	string GetJsonStr(string filename);
	//no need to auto create
	google::protobuf::util::JsonPrintOptions option;
	const char * GetCurDateTimeCStr(struct timeval *pstNowTime);
	

public:
	/*
	发包函数，平台根据ADD_OPMAP所绑定的TRANS_xxx对应的字符串来调用具体的发包函数
	参数说明：
	[IN param] dwUin: 当前机器人编号,一般对应游戏账号
	[IN param] pParam: 平台相关参数
	[Return] : 正常返回0，异常返回1。
	*/
	//auto created code start
	int DoEntityFightPropChangeReasonNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerPropNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoUnfreezeGroupLimitNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoBeginCameraSceneLookNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarDataNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoShowMessageNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarChangeElementTypeReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerLevelRewardUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoBargainTerminateNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEvtCreateGadgetNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarEquipChangeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSetPlayerBirthdayReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoForgeStartReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoTowerTeamSelectReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoMaterialDeleteReturnNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneForceLockNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSetPlayerSignatureReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoStoreItemDelNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoMarkEntityInMinMapNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoTakeBattlePassMissionPointReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEvtBeingHitNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSpringUseReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoStoreItemChangeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEntityFightPropUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarPropChangeReasonNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoTowerFloorRecordChangeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoElementReactionLogNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDoGachaReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEnterWorldFogAreaNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoBargainOfferPriceReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEvtAvatarSitDownNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetPushTipsRewardReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerLogoutNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlatformStopRouteNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSetEntityClientDataNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoWorldOwnerBlossomScheduleInfoNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoQueryPathReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPushTipsAllDataNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerLogoutReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoChallengeRecordNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEnterSceneWeatherAreaNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoTakeBattlePassRewardReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSetOpenStateReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonCandidateTeamKickReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneTransToPointReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetDungeonEntryExploreConditionReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoWatcherAllDataNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEvtBulletMoveNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerInvestigationNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetPlayerSocialDetailReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonCandidateTeamChangeAvatarReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoItemAddHintNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoForgeQueueDataNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoUnlockWorldFogAreaNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoLeaveSceneReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAddRandTaskInfoNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarLifeStateChangeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerSetPauseReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoUnlockTransPointReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPathfindingPingNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPathfindingEnterSceneReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonCandidateTeamCreateReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoWorldPlayerReviveReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarFightPropUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoLogTalkNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDoSetPlayerBornDataNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonCandidateTeamPlayerLeaveNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlatformChangeRouteNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoReliquaryPromoteReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDailyTaskDataNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEvtSetAttackTargetNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetPlayerTokenReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoHitClientTrivialNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoJoinPlayerSceneReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGMShowObstacleReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarCardChangeReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoChangeGameTimeReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonChallengeFinishNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoQuestProgressUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEntityJumpNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSealBattleProgressNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoJoinPlayerFailNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoClientScriptEventNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoClientFpsStatusNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSetSceneWeatherAreaReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetMailItemReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGivingRecordChangeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoCreateMassiveEntityReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoClientAbilityInitBeginNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoBuyGoodsReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoForgeGetQueueDataReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSyncTeamEntityNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoServerTimeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoClientAbilitiesInitFinishCombineNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoQuestDestroyEntityReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoWorldPlayerLocationNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoBackMyWorldReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerDataNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonCandidateTeamRefuseNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonCandidateTeamLeaveReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonWayPointNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerChatNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEvtAnimatorStateChangedNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoWorldPlayerInfoNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetCompoundDataReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneEntityDrownReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoCookDataNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneEntitiesMovesReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoMonsterForceAlertNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAllMarkPointNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoTowerMiddleLevelChangeTeamNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneKickPlayerNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneEntitiesMoveCombineNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoOpenStateChangeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSeaLampFlyLampReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSignInInfoReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoUseItemReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoFinishedParentQuestNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEnterSceneReadyReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSetPlayerHeadImageReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoRefreshBackgroundAvatarReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerApplyEnterMpReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoLevelupCityReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoMonsterAlertChangeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoResinChangeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerPropChangeReasonNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarBuffDelNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSignInInfoOpenNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoCutSceneFinishNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoChooseCurAvatarTeamReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneDataNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoTowerBuffSelectReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoCutSceneBeginNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoWeaponUpgradeReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEvtDestroyGadgetNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoClientPauseNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGrantRewardNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerEnterDungeonReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneEntityDisappearNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonPlayerDieNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneAreaExploreNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarAbilityResetFinishNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoBuyResinReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoWatcherEventTypeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoBonusActivityUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDealAddFriendReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEvtAiSyncSkillCdNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAddQuestContentProgressReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonCandidateTeamDismissNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoActivityPlayOpenAnimNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneKickPlayerReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEvtAvatarStandUpNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerQuitDungeonReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerStoreNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonEntryToBeExploreNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoBattlePassAllDataNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEvtRushMoveNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEnterScenePeerNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoMaterialDeleteUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoTakeInvestigationTargetRewardReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonDieOptionReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEntityFightPropNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetShopmallDataReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonWayPointActivateReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarExpeditionDataNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoObstacleModifyNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEvtEntityRenderersChangedNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoWorktopOptionNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarFetterDataNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerCookArgsReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoCookRecipeDataNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoScenePointUnlockNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoWorldOwnerDailyTaskNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneEntityAppearNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarTeamUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoNpcTalkReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEvtAvatarEnterFocusNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneTeamUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoCookGradeDataNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoChangeAvatarReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoTowerEnterLevelReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerLoginReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoScenePlayerSoundNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoCombineReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEvtBulletDeactiveNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoMarkMapReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEnterTransPointRegionNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarExpeditionAllDataReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoWearEquipReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoBonusActivityInfoReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoBlossomChestInfoNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoBattlePassCurScheduleUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoClientNewMailNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEvtEntityStartDieEndNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoQuestDelNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetSignInRewardReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetGachaInfoReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoBuyShopmallGoodsReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoItemCdGroupTimeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDropItemReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoTakeInvestigationRewardReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoBattlePassMissionUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoMarkNewNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoCreateMassiveEntityNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSealBattleBeginNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoLockWorldFogAreaNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAllSeenMonsterNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAnimatorForceSetAirMoveNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarExpeditionStartReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarUnlockTalentNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoWatcherEventNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAbilityInvocationsNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlatformRouteStateNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPostEnterSceneReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerLuaShellNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGmTalkReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPushTipsChangeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneRouteChangeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEntityMoveRoomNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoTowerLevelEndNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoForgeQueueManipulateReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoTowerAllDataReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetBlossomBriefInfoListReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetActivityScheduleReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoLifeStateChangeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoRemoveRandTaskInfoNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerCompoundMaterialReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoTakeoffEquipReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoActivityScheduleInfoNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoServerBuffChangeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSetUpAvatarTeamReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoReadMailNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoWindSeedClientNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerCookReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEvtDoSkillSuccNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneCreateEntityReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerApplyEnterMpResultNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerChatCDNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonCandidateTeamInviteNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoUnmarkEntityInMinMapNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoTakeCompoundOutputReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoCanUseSkillNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEntityForceSyncReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoExecuteGadgetLuaReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEnterSceneDoneReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSelectWorktopOptionReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoBigTalentPointConvertReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoServerAnnounceNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoQuestUpdateQuestVarReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoTowerLevelStarCondNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDestroyMassiveEntityNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoCutSceneEndNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonFollowNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneAvatarStaminaStepReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetPlayerMpModeAvailabilityReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarAddNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoWatcherChangeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarSkillMaxChargeCountNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonCandidateTeamInviteReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEvtBulletHitNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEvtAiSyncCombatThreatInfoNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoWorldOwnerBlossomBriefInfoNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoOrderFinishNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoCombatInvocationsNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoWeaponAwakenReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoOpenStateUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoTakePlayerLevelRewardReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoWorldPlayerDieNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarEnterElementViewNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarSkillChangeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerQuitFromMpNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAskAddFriendReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAddSeenMonsterNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarFightPropNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoChangeTeamNameReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoStoreWeightLimitNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDailyTaskProgressNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarAbilityResetNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerEnterSceneNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerInvestigationTargetNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoBlossomBriefInfoNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoTowerDailyRewardProgressChangeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoChallengeDataNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetShopmallShopDataReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonShowReminderNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoWeaponPromoteReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPushTipsReadFinishReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoClientTriggerEventNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGivingRecordNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerApplyEnterMpResultReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoProudSkillChangeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoQuestUpdateQuestVarNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneDestroyEntityReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetAllMailReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSetPlayerBornDataReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDropSubfieldReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoBattlePassMissionDelNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoHostPlayerNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarSkillInfoNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoWorldResinChangeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetSceneAreaReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoScenePlayerLocationNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarDelNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoWorldDataNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoRobotPushPlayerDataNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoTowerCurLevelRecordChangeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneInitFinishReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoQuestListNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoFocusAvatarReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoTakeMaterialDeleteReturnReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneAreaUnlockNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetAuthkeyReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoBargainStartNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonCandidateTeamSetReadyReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneTeamMPDisplayCurAvatarNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonChallengeBeginNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEnterWorldAreaReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonCandidateTeamInfoNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEndCameraSceneLookNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoTriggerCreateGadgetToEquipPartNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerSetLanguageReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneEntityMoveNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoClientTransmitReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoQuestListUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPingReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarPromoteReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetDailyDungeonEntryInfoReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneAreaWeatherNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerApplyEnterMpNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoBonusActivityAllDataNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerGameTimeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoItemGivingReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoQuestCreateEntityReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEvtAvatarExitFocusNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoTowerGetFloorStarRewardReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSeaLampTakeContributionRewardReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerRandomCookReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonSlipRevivePointActivateReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoLogCutsceneNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoServerAnnounceRevokeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetBonusActivityRewardReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoQuestDestroyNpcReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGMShowNavMeshReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneForceUnlockNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerPreEnterMpNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDelMailReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoServerLogNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarPropNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoMassiveEntityStateChangedNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetInvestigationMonsterReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoFinishedParentQuestUpdateNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonSettleNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEntityAuthorityChangeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarSkillUpgradeReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerPropChangeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonPlayerDieReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarExpeditionCallBackReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoExecuteGroupTriggerReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetOnlinePlayerListReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoRechargeReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoChangeMpTeamAvatarReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetShopReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetPlayerFriendListReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoBuyWorldResinReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSetPlayerNameReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoServerDisconnectClientNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSeaLampContributeItemReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneTimeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoScenePlayerInfoNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoKeepAliveNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEvtBeingHitsCombineNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoClientAbilityInitFinishNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarBuffAddNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneEntityMoveReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoExitTransPointRegionNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerInvestigationAllInfoNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonEntryInfoReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetQuestTalkHistoryReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSetPlayerPropReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoExitSceneWeatherAreaNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDeleteFriendReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoMonsterSummonTagNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoActivityInfoNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEvtCostStaminaNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoChatHistoryNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonCandidateTeamReplyInviteReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSeeMonsterReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSealBattleEndNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoTowerBriefDataNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoProudSkillExtraLevelNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPersonalSceneJumpReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerEnterSceneInfoNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAbilityInvocationFixedNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoClientReconnectNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarSkillDepotChangeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneGetAreaExplorePercentReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEvtAnimatorParameterNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoLoadActivityTerrainNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonDataNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetScenePointReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSeaLampTakePhaseRewardReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoUnlockAvatarTalentReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGadgetStateNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarUpgradeReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEvtFaceToDirNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDungeonGetStatueDropReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlatformStartRouteNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGadgetInteractReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDailyTaskScoreRewardNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEntityPropNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSceneWeatherForcastReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoMailChangeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetActivityInfoReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEvtFaceToEntityNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoChapterStateNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerChatReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoBossChestActivateNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoTowerSurrenderReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoEvtAvatarUpdateFocusNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoClientReportNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoPlayerTimeNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAbilityInvocationFailNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoReliquaryUpgradeReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoSignInAllDataNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDataResVersionNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDelTeamEntityNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoProudSkillUpgradeReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarExpeditionGetRewardReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoAvatarDieAnimationEndReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoGetSceneNpcPositionReq(unsigned int dwUin, STScriptOpParam *pParam);
	int DoDropHintNotify(unsigned int dwUin, STScriptOpParam *pParam);
	int DoCompoundDataNotify(unsigned int dwUin, STScriptOpParam *pParam);
	//auto created code end

private:
	REGISTERSCRIPTOP_BEGIN(init)
		//事务名称与发包函数地址绑定
		//auto created code start
		ADD_OPMAP(TRANS_EntityFightPropChangeReasonNotify, &CG4GameScriptOp::DoEntityFightPropChangeReasonNotify)
		ADD_OPMAP(TRANS_PlayerPropNotify, &CG4GameScriptOp::DoPlayerPropNotify)
		ADD_OPMAP(TRANS_UnfreezeGroupLimitNotify, &CG4GameScriptOp::DoUnfreezeGroupLimitNotify)
		ADD_OPMAP(TRANS_BeginCameraSceneLookNotify, &CG4GameScriptOp::DoBeginCameraSceneLookNotify)
		ADD_OPMAP(TRANS_AvatarDataNotify, &CG4GameScriptOp::DoAvatarDataNotify)
		ADD_OPMAP(TRANS_ShowMessageNotify, &CG4GameScriptOp::DoShowMessageNotify)
		ADD_OPMAP(TRANS_AvatarChangeElementTypeReq, &CG4GameScriptOp::DoAvatarChangeElementTypeReq)
		ADD_OPMAP(TRANS_PlayerLevelRewardUpdateNotify, &CG4GameScriptOp::DoPlayerLevelRewardUpdateNotify)
		ADD_OPMAP(TRANS_BargainTerminateNotify, &CG4GameScriptOp::DoBargainTerminateNotify)
		ADD_OPMAP(TRANS_EvtCreateGadgetNotify, &CG4GameScriptOp::DoEvtCreateGadgetNotify)
		ADD_OPMAP(TRANS_AvatarEquipChangeNotify, &CG4GameScriptOp::DoAvatarEquipChangeNotify)
		ADD_OPMAP(TRANS_SetPlayerBirthdayReq, &CG4GameScriptOp::DoSetPlayerBirthdayReq)
		ADD_OPMAP(TRANS_ForgeStartReq, &CG4GameScriptOp::DoForgeStartReq)
		ADD_OPMAP(TRANS_TowerTeamSelectReq, &CG4GameScriptOp::DoTowerTeamSelectReq)
		ADD_OPMAP(TRANS_MaterialDeleteReturnNotify, &CG4GameScriptOp::DoMaterialDeleteReturnNotify)
		ADD_OPMAP(TRANS_SceneForceLockNotify, &CG4GameScriptOp::DoSceneForceLockNotify)
		ADD_OPMAP(TRANS_SetPlayerSignatureReq, &CG4GameScriptOp::DoSetPlayerSignatureReq)
		ADD_OPMAP(TRANS_StoreItemDelNotify, &CG4GameScriptOp::DoStoreItemDelNotify)
		ADD_OPMAP(TRANS_MarkEntityInMinMapNotify, &CG4GameScriptOp::DoMarkEntityInMinMapNotify)
		ADD_OPMAP(TRANS_TakeBattlePassMissionPointReq, &CG4GameScriptOp::DoTakeBattlePassMissionPointReq)
		ADD_OPMAP(TRANS_EvtBeingHitNotify, &CG4GameScriptOp::DoEvtBeingHitNotify)
		ADD_OPMAP(TRANS_SpringUseReq, &CG4GameScriptOp::DoSpringUseReq)
		ADD_OPMAP(TRANS_StoreItemChangeNotify, &CG4GameScriptOp::DoStoreItemChangeNotify)
		ADD_OPMAP(TRANS_EntityFightPropUpdateNotify, &CG4GameScriptOp::DoEntityFightPropUpdateNotify)
		ADD_OPMAP(TRANS_AvatarPropChangeReasonNotify, &CG4GameScriptOp::DoAvatarPropChangeReasonNotify)
		ADD_OPMAP(TRANS_TowerFloorRecordChangeNotify, &CG4GameScriptOp::DoTowerFloorRecordChangeNotify)
		ADD_OPMAP(TRANS_ElementReactionLogNotify, &CG4GameScriptOp::DoElementReactionLogNotify)
		ADD_OPMAP(TRANS_DoGachaReq, &CG4GameScriptOp::DoDoGachaReq)
		ADD_OPMAP(TRANS_EnterWorldFogAreaNotify, &CG4GameScriptOp::DoEnterWorldFogAreaNotify)
		ADD_OPMAP(TRANS_BargainOfferPriceReq, &CG4GameScriptOp::DoBargainOfferPriceReq)
		ADD_OPMAP(TRANS_EvtAvatarSitDownNotify, &CG4GameScriptOp::DoEvtAvatarSitDownNotify)
		ADD_OPMAP(TRANS_GetPushTipsRewardReq, &CG4GameScriptOp::DoGetPushTipsRewardReq)
		ADD_OPMAP(TRANS_PlayerLogoutNotify, &CG4GameScriptOp::DoPlayerLogoutNotify)
		ADD_OPMAP(TRANS_PlatformStopRouteNotify, &CG4GameScriptOp::DoPlatformStopRouteNotify)
		ADD_OPMAP(TRANS_SetEntityClientDataNotify, &CG4GameScriptOp::DoSetEntityClientDataNotify)
		ADD_OPMAP(TRANS_WorldOwnerBlossomScheduleInfoNotify, &CG4GameScriptOp::DoWorldOwnerBlossomScheduleInfoNotify)
		ADD_OPMAP(TRANS_QueryPathReq, &CG4GameScriptOp::DoQueryPathReq)
		ADD_OPMAP(TRANS_PushTipsAllDataNotify, &CG4GameScriptOp::DoPushTipsAllDataNotify)
		ADD_OPMAP(TRANS_PlayerLogoutReq, &CG4GameScriptOp::DoPlayerLogoutReq)
		ADD_OPMAP(TRANS_ChallengeRecordNotify, &CG4GameScriptOp::DoChallengeRecordNotify)
		ADD_OPMAP(TRANS_EnterSceneWeatherAreaNotify, &CG4GameScriptOp::DoEnterSceneWeatherAreaNotify)
		ADD_OPMAP(TRANS_TakeBattlePassRewardReq, &CG4GameScriptOp::DoTakeBattlePassRewardReq)
		ADD_OPMAP(TRANS_SetOpenStateReq, &CG4GameScriptOp::DoSetOpenStateReq)
		ADD_OPMAP(TRANS_DungeonCandidateTeamKickReq, &CG4GameScriptOp::DoDungeonCandidateTeamKickReq)
		ADD_OPMAP(TRANS_SceneTransToPointReq, &CG4GameScriptOp::DoSceneTransToPointReq)
		ADD_OPMAP(TRANS_GetDungeonEntryExploreConditionReq, &CG4GameScriptOp::DoGetDungeonEntryExploreConditionReq)
		ADD_OPMAP(TRANS_WatcherAllDataNotify, &CG4GameScriptOp::DoWatcherAllDataNotify)
		ADD_OPMAP(TRANS_EvtBulletMoveNotify, &CG4GameScriptOp::DoEvtBulletMoveNotify)
		ADD_OPMAP(TRANS_PlayerInvestigationNotify, &CG4GameScriptOp::DoPlayerInvestigationNotify)
		ADD_OPMAP(TRANS_GetPlayerSocialDetailReq, &CG4GameScriptOp::DoGetPlayerSocialDetailReq)
		ADD_OPMAP(TRANS_DungeonCandidateTeamChangeAvatarReq, &CG4GameScriptOp::DoDungeonCandidateTeamChangeAvatarReq)
		ADD_OPMAP(TRANS_ItemAddHintNotify, &CG4GameScriptOp::DoItemAddHintNotify)
		ADD_OPMAP(TRANS_ForgeQueueDataNotify, &CG4GameScriptOp::DoForgeQueueDataNotify)
		ADD_OPMAP(TRANS_UnlockWorldFogAreaNotify, &CG4GameScriptOp::DoUnlockWorldFogAreaNotify)
		ADD_OPMAP(TRANS_LeaveSceneReq, &CG4GameScriptOp::DoLeaveSceneReq)
		ADD_OPMAP(TRANS_AddRandTaskInfoNotify, &CG4GameScriptOp::DoAddRandTaskInfoNotify)
		ADD_OPMAP(TRANS_AvatarLifeStateChangeNotify, &CG4GameScriptOp::DoAvatarLifeStateChangeNotify)
		ADD_OPMAP(TRANS_PlayerSetPauseReq, &CG4GameScriptOp::DoPlayerSetPauseReq)
		ADD_OPMAP(TRANS_UnlockTransPointReq, &CG4GameScriptOp::DoUnlockTransPointReq)
		ADD_OPMAP(TRANS_PathfindingPingNotify, &CG4GameScriptOp::DoPathfindingPingNotify)
		ADD_OPMAP(TRANS_PathfindingEnterSceneReq, &CG4GameScriptOp::DoPathfindingEnterSceneReq)
		ADD_OPMAP(TRANS_DungeonCandidateTeamCreateReq, &CG4GameScriptOp::DoDungeonCandidateTeamCreateReq)
		ADD_OPMAP(TRANS_WorldPlayerReviveReq, &CG4GameScriptOp::DoWorldPlayerReviveReq)
		ADD_OPMAP(TRANS_AvatarFightPropUpdateNotify, &CG4GameScriptOp::DoAvatarFightPropUpdateNotify)
		ADD_OPMAP(TRANS_LogTalkNotify, &CG4GameScriptOp::DoLogTalkNotify)
		ADD_OPMAP(TRANS_DoSetPlayerBornDataNotify, &CG4GameScriptOp::DoDoSetPlayerBornDataNotify)
		ADD_OPMAP(TRANS_DungeonCandidateTeamPlayerLeaveNotify, &CG4GameScriptOp::DoDungeonCandidateTeamPlayerLeaveNotify)
		ADD_OPMAP(TRANS_PlatformChangeRouteNotify, &CG4GameScriptOp::DoPlatformChangeRouteNotify)
		ADD_OPMAP(TRANS_ReliquaryPromoteReq, &CG4GameScriptOp::DoReliquaryPromoteReq)
		ADD_OPMAP(TRANS_DailyTaskDataNotify, &CG4GameScriptOp::DoDailyTaskDataNotify)
		ADD_OPMAP(TRANS_EvtSetAttackTargetNotify, &CG4GameScriptOp::DoEvtSetAttackTargetNotify)
		ADD_OPMAP(TRANS_GetPlayerTokenReq, &CG4GameScriptOp::DoGetPlayerTokenReq)
		ADD_OPMAP(TRANS_HitClientTrivialNotify, &CG4GameScriptOp::DoHitClientTrivialNotify)
		ADD_OPMAP(TRANS_JoinPlayerSceneReq, &CG4GameScriptOp::DoJoinPlayerSceneReq)
		ADD_OPMAP(TRANS_GMShowObstacleReq, &CG4GameScriptOp::DoGMShowObstacleReq)
		ADD_OPMAP(TRANS_AvatarCardChangeReq, &CG4GameScriptOp::DoAvatarCardChangeReq)
		ADD_OPMAP(TRANS_ChangeGameTimeReq, &CG4GameScriptOp::DoChangeGameTimeReq)
		ADD_OPMAP(TRANS_DungeonChallengeFinishNotify, &CG4GameScriptOp::DoDungeonChallengeFinishNotify)
		ADD_OPMAP(TRANS_QuestProgressUpdateNotify, &CG4GameScriptOp::DoQuestProgressUpdateNotify)
		ADD_OPMAP(TRANS_EntityJumpNotify, &CG4GameScriptOp::DoEntityJumpNotify)
		ADD_OPMAP(TRANS_SealBattleProgressNotify, &CG4GameScriptOp::DoSealBattleProgressNotify)
		ADD_OPMAP(TRANS_JoinPlayerFailNotify, &CG4GameScriptOp::DoJoinPlayerFailNotify)
		ADD_OPMAP(TRANS_ClientScriptEventNotify, &CG4GameScriptOp::DoClientScriptEventNotify)
		ADD_OPMAP(TRANS_ClientFpsStatusNotify, &CG4GameScriptOp::DoClientFpsStatusNotify)
		ADD_OPMAP(TRANS_SetSceneWeatherAreaReq, &CG4GameScriptOp::DoSetSceneWeatherAreaReq)
		ADD_OPMAP(TRANS_GetMailItemReq, &CG4GameScriptOp::DoGetMailItemReq)
		ADD_OPMAP(TRANS_GivingRecordChangeNotify, &CG4GameScriptOp::DoGivingRecordChangeNotify)
		ADD_OPMAP(TRANS_CreateMassiveEntityReq, &CG4GameScriptOp::DoCreateMassiveEntityReq)
		ADD_OPMAP(TRANS_ClientAbilityInitBeginNotify, &CG4GameScriptOp::DoClientAbilityInitBeginNotify)
		ADD_OPMAP(TRANS_BuyGoodsReq, &CG4GameScriptOp::DoBuyGoodsReq)
		ADD_OPMAP(TRANS_ForgeGetQueueDataReq, &CG4GameScriptOp::DoForgeGetQueueDataReq)
		ADD_OPMAP(TRANS_SyncTeamEntityNotify, &CG4GameScriptOp::DoSyncTeamEntityNotify)
		ADD_OPMAP(TRANS_ServerTimeNotify, &CG4GameScriptOp::DoServerTimeNotify)
		ADD_OPMAP(TRANS_ClientAbilitiesInitFinishCombineNotify, &CG4GameScriptOp::DoClientAbilitiesInitFinishCombineNotify)
		ADD_OPMAP(TRANS_QuestDestroyEntityReq, &CG4GameScriptOp::DoQuestDestroyEntityReq)
		ADD_OPMAP(TRANS_WorldPlayerLocationNotify, &CG4GameScriptOp::DoWorldPlayerLocationNotify)
		ADD_OPMAP(TRANS_BackMyWorldReq, &CG4GameScriptOp::DoBackMyWorldReq)
		ADD_OPMAP(TRANS_PlayerDataNotify, &CG4GameScriptOp::DoPlayerDataNotify)
		ADD_OPMAP(TRANS_DungeonCandidateTeamRefuseNotify, &CG4GameScriptOp::DoDungeonCandidateTeamRefuseNotify)
		ADD_OPMAP(TRANS_DungeonCandidateTeamLeaveReq, &CG4GameScriptOp::DoDungeonCandidateTeamLeaveReq)
		ADD_OPMAP(TRANS_DungeonWayPointNotify, &CG4GameScriptOp::DoDungeonWayPointNotify)
		ADD_OPMAP(TRANS_PlayerChatNotify, &CG4GameScriptOp::DoPlayerChatNotify)
		ADD_OPMAP(TRANS_EvtAnimatorStateChangedNotify, &CG4GameScriptOp::DoEvtAnimatorStateChangedNotify)
		ADD_OPMAP(TRANS_WorldPlayerInfoNotify, &CG4GameScriptOp::DoWorldPlayerInfoNotify)
		ADD_OPMAP(TRANS_GetCompoundDataReq, &CG4GameScriptOp::DoGetCompoundDataReq)
		ADD_OPMAP(TRANS_SceneEntityDrownReq, &CG4GameScriptOp::DoSceneEntityDrownReq)
		ADD_OPMAP(TRANS_CookDataNotify, &CG4GameScriptOp::DoCookDataNotify)
		ADD_OPMAP(TRANS_SceneEntitiesMovesReq, &CG4GameScriptOp::DoSceneEntitiesMovesReq)
		ADD_OPMAP(TRANS_MonsterForceAlertNotify, &CG4GameScriptOp::DoMonsterForceAlertNotify)
		ADD_OPMAP(TRANS_AllMarkPointNotify, &CG4GameScriptOp::DoAllMarkPointNotify)
		ADD_OPMAP(TRANS_TowerMiddleLevelChangeTeamNotify, &CG4GameScriptOp::DoTowerMiddleLevelChangeTeamNotify)
		ADD_OPMAP(TRANS_SceneKickPlayerNotify, &CG4GameScriptOp::DoSceneKickPlayerNotify)
		ADD_OPMAP(TRANS_SceneEntitiesMoveCombineNotify, &CG4GameScriptOp::DoSceneEntitiesMoveCombineNotify)
		ADD_OPMAP(TRANS_OpenStateChangeNotify, &CG4GameScriptOp::DoOpenStateChangeNotify)
		ADD_OPMAP(TRANS_SeaLampFlyLampReq, &CG4GameScriptOp::DoSeaLampFlyLampReq)
		ADD_OPMAP(TRANS_SignInInfoReq, &CG4GameScriptOp::DoSignInInfoReq)
		ADD_OPMAP(TRANS_UseItemReq, &CG4GameScriptOp::DoUseItemReq)
		ADD_OPMAP(TRANS_FinishedParentQuestNotify, &CG4GameScriptOp::DoFinishedParentQuestNotify)
		ADD_OPMAP(TRANS_EnterSceneReadyReq, &CG4GameScriptOp::DoEnterSceneReadyReq)
		ADD_OPMAP(TRANS_SetPlayerHeadImageReq, &CG4GameScriptOp::DoSetPlayerHeadImageReq)
		ADD_OPMAP(TRANS_RefreshBackgroundAvatarReq, &CG4GameScriptOp::DoRefreshBackgroundAvatarReq)
		ADD_OPMAP(TRANS_PlayerApplyEnterMpReq, &CG4GameScriptOp::DoPlayerApplyEnterMpReq)
		ADD_OPMAP(TRANS_LevelupCityReq, &CG4GameScriptOp::DoLevelupCityReq)
		ADD_OPMAP(TRANS_MonsterAlertChangeNotify, &CG4GameScriptOp::DoMonsterAlertChangeNotify)
		ADD_OPMAP(TRANS_ResinChangeNotify, &CG4GameScriptOp::DoResinChangeNotify)
		ADD_OPMAP(TRANS_PlayerPropChangeReasonNotify, &CG4GameScriptOp::DoPlayerPropChangeReasonNotify)
		ADD_OPMAP(TRANS_AvatarBuffDelNotify, &CG4GameScriptOp::DoAvatarBuffDelNotify)
		ADD_OPMAP(TRANS_SignInInfoOpenNotify, &CG4GameScriptOp::DoSignInInfoOpenNotify)
		ADD_OPMAP(TRANS_CutSceneFinishNotify, &CG4GameScriptOp::DoCutSceneFinishNotify)
		ADD_OPMAP(TRANS_ChooseCurAvatarTeamReq, &CG4GameScriptOp::DoChooseCurAvatarTeamReq)
		ADD_OPMAP(TRANS_SceneDataNotify, &CG4GameScriptOp::DoSceneDataNotify)
		ADD_OPMAP(TRANS_TowerBuffSelectReq, &CG4GameScriptOp::DoTowerBuffSelectReq)
		ADD_OPMAP(TRANS_CutSceneBeginNotify, &CG4GameScriptOp::DoCutSceneBeginNotify)
		ADD_OPMAP(TRANS_WeaponUpgradeReq, &CG4GameScriptOp::DoWeaponUpgradeReq)
		ADD_OPMAP(TRANS_EvtDestroyGadgetNotify, &CG4GameScriptOp::DoEvtDestroyGadgetNotify)
		ADD_OPMAP(TRANS_ClientPauseNotify, &CG4GameScriptOp::DoClientPauseNotify)
		ADD_OPMAP(TRANS_GrantRewardNotify, &CG4GameScriptOp::DoGrantRewardNotify)
		ADD_OPMAP(TRANS_PlayerEnterDungeonReq, &CG4GameScriptOp::DoPlayerEnterDungeonReq)
		ADD_OPMAP(TRANS_SceneEntityDisappearNotify, &CG4GameScriptOp::DoSceneEntityDisappearNotify)
		ADD_OPMAP(TRANS_DungeonPlayerDieNotify, &CG4GameScriptOp::DoDungeonPlayerDieNotify)
		ADD_OPMAP(TRANS_SceneAreaExploreNotify, &CG4GameScriptOp::DoSceneAreaExploreNotify)
		ADD_OPMAP(TRANS_AvatarAbilityResetFinishNotify, &CG4GameScriptOp::DoAvatarAbilityResetFinishNotify)
		ADD_OPMAP(TRANS_BuyResinReq, &CG4GameScriptOp::DoBuyResinReq)
		ADD_OPMAP(TRANS_WatcherEventTypeNotify, &CG4GameScriptOp::DoWatcherEventTypeNotify)
		ADD_OPMAP(TRANS_BonusActivityUpdateNotify, &CG4GameScriptOp::DoBonusActivityUpdateNotify)
		ADD_OPMAP(TRANS_DealAddFriendReq, &CG4GameScriptOp::DoDealAddFriendReq)
		ADD_OPMAP(TRANS_EvtAiSyncSkillCdNotify, &CG4GameScriptOp::DoEvtAiSyncSkillCdNotify)
		ADD_OPMAP(TRANS_AddQuestContentProgressReq, &CG4GameScriptOp::DoAddQuestContentProgressReq)
		ADD_OPMAP(TRANS_DungeonCandidateTeamDismissNotify, &CG4GameScriptOp::DoDungeonCandidateTeamDismissNotify)
		ADD_OPMAP(TRANS_ActivityPlayOpenAnimNotify, &CG4GameScriptOp::DoActivityPlayOpenAnimNotify)
		ADD_OPMAP(TRANS_SceneKickPlayerReq, &CG4GameScriptOp::DoSceneKickPlayerReq)
		ADD_OPMAP(TRANS_EvtAvatarStandUpNotify, &CG4GameScriptOp::DoEvtAvatarStandUpNotify)
		ADD_OPMAP(TRANS_PlayerQuitDungeonReq, &CG4GameScriptOp::DoPlayerQuitDungeonReq)
		ADD_OPMAP(TRANS_PlayerStoreNotify, &CG4GameScriptOp::DoPlayerStoreNotify)
		ADD_OPMAP(TRANS_DungeonEntryToBeExploreNotify, &CG4GameScriptOp::DoDungeonEntryToBeExploreNotify)
		ADD_OPMAP(TRANS_BattlePassAllDataNotify, &CG4GameScriptOp::DoBattlePassAllDataNotify)
		ADD_OPMAP(TRANS_EvtRushMoveNotify, &CG4GameScriptOp::DoEvtRushMoveNotify)
		ADD_OPMAP(TRANS_EnterScenePeerNotify, &CG4GameScriptOp::DoEnterScenePeerNotify)
		ADD_OPMAP(TRANS_MaterialDeleteUpdateNotify, &CG4GameScriptOp::DoMaterialDeleteUpdateNotify)
		ADD_OPMAP(TRANS_TakeInvestigationTargetRewardReq, &CG4GameScriptOp::DoTakeInvestigationTargetRewardReq)
		ADD_OPMAP(TRANS_DungeonDieOptionReq, &CG4GameScriptOp::DoDungeonDieOptionReq)
		ADD_OPMAP(TRANS_EntityFightPropNotify, &CG4GameScriptOp::DoEntityFightPropNotify)
		ADD_OPMAP(TRANS_GetShopmallDataReq, &CG4GameScriptOp::DoGetShopmallDataReq)
		ADD_OPMAP(TRANS_DungeonWayPointActivateReq, &CG4GameScriptOp::DoDungeonWayPointActivateReq)
		ADD_OPMAP(TRANS_AvatarExpeditionDataNotify, &CG4GameScriptOp::DoAvatarExpeditionDataNotify)
		ADD_OPMAP(TRANS_ObstacleModifyNotify, &CG4GameScriptOp::DoObstacleModifyNotify)
		ADD_OPMAP(TRANS_EvtEntityRenderersChangedNotify, &CG4GameScriptOp::DoEvtEntityRenderersChangedNotify)
		ADD_OPMAP(TRANS_WorktopOptionNotify, &CG4GameScriptOp::DoWorktopOptionNotify)
		ADD_OPMAP(TRANS_AvatarFetterDataNotify, &CG4GameScriptOp::DoAvatarFetterDataNotify)
		ADD_OPMAP(TRANS_PlayerCookArgsReq, &CG4GameScriptOp::DoPlayerCookArgsReq)
		ADD_OPMAP(TRANS_CookRecipeDataNotify, &CG4GameScriptOp::DoCookRecipeDataNotify)
		ADD_OPMAP(TRANS_ScenePointUnlockNotify, &CG4GameScriptOp::DoScenePointUnlockNotify)
		ADD_OPMAP(TRANS_WorldOwnerDailyTaskNotify, &CG4GameScriptOp::DoWorldOwnerDailyTaskNotify)
		ADD_OPMAP(TRANS_SceneEntityAppearNotify, &CG4GameScriptOp::DoSceneEntityAppearNotify)
		ADD_OPMAP(TRANS_AvatarTeamUpdateNotify, &CG4GameScriptOp::DoAvatarTeamUpdateNotify)
		ADD_OPMAP(TRANS_NpcTalkReq, &CG4GameScriptOp::DoNpcTalkReq)
		ADD_OPMAP(TRANS_EvtAvatarEnterFocusNotify, &CG4GameScriptOp::DoEvtAvatarEnterFocusNotify)
		ADD_OPMAP(TRANS_SceneTeamUpdateNotify, &CG4GameScriptOp::DoSceneTeamUpdateNotify)
		ADD_OPMAP(TRANS_CookGradeDataNotify, &CG4GameScriptOp::DoCookGradeDataNotify)
		ADD_OPMAP(TRANS_ChangeAvatarReq, &CG4GameScriptOp::DoChangeAvatarReq)
		ADD_OPMAP(TRANS_TowerEnterLevelReq, &CG4GameScriptOp::DoTowerEnterLevelReq)
		ADD_OPMAP(TRANS_PlayerLoginReq, &CG4GameScriptOp::DoPlayerLoginReq)
		ADD_OPMAP(TRANS_ScenePlayerSoundNotify, &CG4GameScriptOp::DoScenePlayerSoundNotify)
		ADD_OPMAP(TRANS_CombineReq, &CG4GameScriptOp::DoCombineReq)
		ADD_OPMAP(TRANS_EvtBulletDeactiveNotify, &CG4GameScriptOp::DoEvtBulletDeactiveNotify)
		ADD_OPMAP(TRANS_MarkMapReq, &CG4GameScriptOp::DoMarkMapReq)
		ADD_OPMAP(TRANS_EnterTransPointRegionNotify, &CG4GameScriptOp::DoEnterTransPointRegionNotify)
		ADD_OPMAP(TRANS_AvatarExpeditionAllDataReq, &CG4GameScriptOp::DoAvatarExpeditionAllDataReq)
		ADD_OPMAP(TRANS_WearEquipReq, &CG4GameScriptOp::DoWearEquipReq)
		ADD_OPMAP(TRANS_BonusActivityInfoReq, &CG4GameScriptOp::DoBonusActivityInfoReq)
		ADD_OPMAP(TRANS_BlossomChestInfoNotify, &CG4GameScriptOp::DoBlossomChestInfoNotify)
		ADD_OPMAP(TRANS_BattlePassCurScheduleUpdateNotify, &CG4GameScriptOp::DoBattlePassCurScheduleUpdateNotify)
		ADD_OPMAP(TRANS_ClientNewMailNotify, &CG4GameScriptOp::DoClientNewMailNotify)
		ADD_OPMAP(TRANS_EvtEntityStartDieEndNotify, &CG4GameScriptOp::DoEvtEntityStartDieEndNotify)
		ADD_OPMAP(TRANS_QuestDelNotify, &CG4GameScriptOp::DoQuestDelNotify)
		ADD_OPMAP(TRANS_GetSignInRewardReq, &CG4GameScriptOp::DoGetSignInRewardReq)
		ADD_OPMAP(TRANS_GetGachaInfoReq, &CG4GameScriptOp::DoGetGachaInfoReq)
		ADD_OPMAP(TRANS_BuyShopmallGoodsReq, &CG4GameScriptOp::DoBuyShopmallGoodsReq)
		ADD_OPMAP(TRANS_ItemCdGroupTimeNotify, &CG4GameScriptOp::DoItemCdGroupTimeNotify)
		ADD_OPMAP(TRANS_DropItemReq, &CG4GameScriptOp::DoDropItemReq)
		ADD_OPMAP(TRANS_TakeInvestigationRewardReq, &CG4GameScriptOp::DoTakeInvestigationRewardReq)
		ADD_OPMAP(TRANS_BattlePassMissionUpdateNotify, &CG4GameScriptOp::DoBattlePassMissionUpdateNotify)
		ADD_OPMAP(TRANS_MarkNewNotify, &CG4GameScriptOp::DoMarkNewNotify)
		ADD_OPMAP(TRANS_CreateMassiveEntityNotify, &CG4GameScriptOp::DoCreateMassiveEntityNotify)
		ADD_OPMAP(TRANS_SealBattleBeginNotify, &CG4GameScriptOp::DoSealBattleBeginNotify)
		ADD_OPMAP(TRANS_LockWorldFogAreaNotify, &CG4GameScriptOp::DoLockWorldFogAreaNotify)
		ADD_OPMAP(TRANS_AllSeenMonsterNotify, &CG4GameScriptOp::DoAllSeenMonsterNotify)
		ADD_OPMAP(TRANS_AnimatorForceSetAirMoveNotify, &CG4GameScriptOp::DoAnimatorForceSetAirMoveNotify)
		ADD_OPMAP(TRANS_AvatarExpeditionStartReq, &CG4GameScriptOp::DoAvatarExpeditionStartReq)
		ADD_OPMAP(TRANS_AvatarUnlockTalentNotify, &CG4GameScriptOp::DoAvatarUnlockTalentNotify)
		ADD_OPMAP(TRANS_WatcherEventNotify, &CG4GameScriptOp::DoWatcherEventNotify)
		ADD_OPMAP(TRANS_AbilityInvocationsNotify, &CG4GameScriptOp::DoAbilityInvocationsNotify)
		ADD_OPMAP(TRANS_PlatformRouteStateNotify, &CG4GameScriptOp::DoPlatformRouteStateNotify)
		ADD_OPMAP(TRANS_PostEnterSceneReq, &CG4GameScriptOp::DoPostEnterSceneReq)
		ADD_OPMAP(TRANS_PlayerLuaShellNotify, &CG4GameScriptOp::DoPlayerLuaShellNotify)
		ADD_OPMAP(TRANS_GmTalkReq, &CG4GameScriptOp::DoGmTalkReq)
		ADD_OPMAP(TRANS_PushTipsChangeNotify, &CG4GameScriptOp::DoPushTipsChangeNotify)
		ADD_OPMAP(TRANS_SceneRouteChangeNotify, &CG4GameScriptOp::DoSceneRouteChangeNotify)
		ADD_OPMAP(TRANS_EntityMoveRoomNotify, &CG4GameScriptOp::DoEntityMoveRoomNotify)
		ADD_OPMAP(TRANS_TowerLevelEndNotify, &CG4GameScriptOp::DoTowerLevelEndNotify)
		ADD_OPMAP(TRANS_ForgeQueueManipulateReq, &CG4GameScriptOp::DoForgeQueueManipulateReq)
		ADD_OPMAP(TRANS_TowerAllDataReq, &CG4GameScriptOp::DoTowerAllDataReq)
		ADD_OPMAP(TRANS_GetBlossomBriefInfoListReq, &CG4GameScriptOp::DoGetBlossomBriefInfoListReq)
		ADD_OPMAP(TRANS_GetActivityScheduleReq, &CG4GameScriptOp::DoGetActivityScheduleReq)
		ADD_OPMAP(TRANS_LifeStateChangeNotify, &CG4GameScriptOp::DoLifeStateChangeNotify)
		ADD_OPMAP(TRANS_RemoveRandTaskInfoNotify, &CG4GameScriptOp::DoRemoveRandTaskInfoNotify)
		ADD_OPMAP(TRANS_PlayerCompoundMaterialReq, &CG4GameScriptOp::DoPlayerCompoundMaterialReq)
		ADD_OPMAP(TRANS_TakeoffEquipReq, &CG4GameScriptOp::DoTakeoffEquipReq)
		ADD_OPMAP(TRANS_ActivityScheduleInfoNotify, &CG4GameScriptOp::DoActivityScheduleInfoNotify)
		ADD_OPMAP(TRANS_ServerBuffChangeNotify, &CG4GameScriptOp::DoServerBuffChangeNotify)
		ADD_OPMAP(TRANS_SetUpAvatarTeamReq, &CG4GameScriptOp::DoSetUpAvatarTeamReq)
		ADD_OPMAP(TRANS_ReadMailNotify, &CG4GameScriptOp::DoReadMailNotify)
		ADD_OPMAP(TRANS_WindSeedClientNotify, &CG4GameScriptOp::DoWindSeedClientNotify)
		ADD_OPMAP(TRANS_PlayerCookReq, &CG4GameScriptOp::DoPlayerCookReq)
		ADD_OPMAP(TRANS_EvtDoSkillSuccNotify, &CG4GameScriptOp::DoEvtDoSkillSuccNotify)
		ADD_OPMAP(TRANS_SceneCreateEntityReq, &CG4GameScriptOp::DoSceneCreateEntityReq)
		ADD_OPMAP(TRANS_PlayerApplyEnterMpResultNotify, &CG4GameScriptOp::DoPlayerApplyEnterMpResultNotify)
		ADD_OPMAP(TRANS_PlayerChatCDNotify, &CG4GameScriptOp::DoPlayerChatCDNotify)
		ADD_OPMAP(TRANS_DungeonCandidateTeamInviteNotify, &CG4GameScriptOp::DoDungeonCandidateTeamInviteNotify)
		ADD_OPMAP(TRANS_UnmarkEntityInMinMapNotify, &CG4GameScriptOp::DoUnmarkEntityInMinMapNotify)
		ADD_OPMAP(TRANS_TakeCompoundOutputReq, &CG4GameScriptOp::DoTakeCompoundOutputReq)
		ADD_OPMAP(TRANS_CanUseSkillNotify, &CG4GameScriptOp::DoCanUseSkillNotify)
		ADD_OPMAP(TRANS_EntityForceSyncReq, &CG4GameScriptOp::DoEntityForceSyncReq)
		ADD_OPMAP(TRANS_ExecuteGadgetLuaReq, &CG4GameScriptOp::DoExecuteGadgetLuaReq)
		ADD_OPMAP(TRANS_EnterSceneDoneReq, &CG4GameScriptOp::DoEnterSceneDoneReq)
		ADD_OPMAP(TRANS_SelectWorktopOptionReq, &CG4GameScriptOp::DoSelectWorktopOptionReq)
		ADD_OPMAP(TRANS_BigTalentPointConvertReq, &CG4GameScriptOp::DoBigTalentPointConvertReq)
		ADD_OPMAP(TRANS_ServerAnnounceNotify, &CG4GameScriptOp::DoServerAnnounceNotify)
		ADD_OPMAP(TRANS_QuestUpdateQuestVarReq, &CG4GameScriptOp::DoQuestUpdateQuestVarReq)
		ADD_OPMAP(TRANS_TowerLevelStarCondNotify, &CG4GameScriptOp::DoTowerLevelStarCondNotify)
		ADD_OPMAP(TRANS_DestroyMassiveEntityNotify, &CG4GameScriptOp::DoDestroyMassiveEntityNotify)
		ADD_OPMAP(TRANS_CutSceneEndNotify, &CG4GameScriptOp::DoCutSceneEndNotify)
		ADD_OPMAP(TRANS_DungeonFollowNotify, &CG4GameScriptOp::DoDungeonFollowNotify)
		ADD_OPMAP(TRANS_SceneAvatarStaminaStepReq, &CG4GameScriptOp::DoSceneAvatarStaminaStepReq)
		ADD_OPMAP(TRANS_GetPlayerMpModeAvailabilityReq, &CG4GameScriptOp::DoGetPlayerMpModeAvailabilityReq)
		ADD_OPMAP(TRANS_AvatarAddNotify, &CG4GameScriptOp::DoAvatarAddNotify)
		ADD_OPMAP(TRANS_WatcherChangeNotify, &CG4GameScriptOp::DoWatcherChangeNotify)
		ADD_OPMAP(TRANS_AvatarSkillMaxChargeCountNotify, &CG4GameScriptOp::DoAvatarSkillMaxChargeCountNotify)
		ADD_OPMAP(TRANS_DungeonCandidateTeamInviteReq, &CG4GameScriptOp::DoDungeonCandidateTeamInviteReq)
		ADD_OPMAP(TRANS_EvtBulletHitNotify, &CG4GameScriptOp::DoEvtBulletHitNotify)
		ADD_OPMAP(TRANS_EvtAiSyncCombatThreatInfoNotify, &CG4GameScriptOp::DoEvtAiSyncCombatThreatInfoNotify)
		ADD_OPMAP(TRANS_WorldOwnerBlossomBriefInfoNotify, &CG4GameScriptOp::DoWorldOwnerBlossomBriefInfoNotify)
		ADD_OPMAP(TRANS_OrderFinishNotify, &CG4GameScriptOp::DoOrderFinishNotify)
		ADD_OPMAP(TRANS_CombatInvocationsNotify, &CG4GameScriptOp::DoCombatInvocationsNotify)
		ADD_OPMAP(TRANS_WeaponAwakenReq, &CG4GameScriptOp::DoWeaponAwakenReq)
		ADD_OPMAP(TRANS_OpenStateUpdateNotify, &CG4GameScriptOp::DoOpenStateUpdateNotify)
		ADD_OPMAP(TRANS_TakePlayerLevelRewardReq, &CG4GameScriptOp::DoTakePlayerLevelRewardReq)
		ADD_OPMAP(TRANS_WorldPlayerDieNotify, &CG4GameScriptOp::DoWorldPlayerDieNotify)
		ADD_OPMAP(TRANS_AvatarEnterElementViewNotify, &CG4GameScriptOp::DoAvatarEnterElementViewNotify)
		ADD_OPMAP(TRANS_AvatarSkillChangeNotify, &CG4GameScriptOp::DoAvatarSkillChangeNotify)
		ADD_OPMAP(TRANS_PlayerQuitFromMpNotify, &CG4GameScriptOp::DoPlayerQuitFromMpNotify)
		ADD_OPMAP(TRANS_AskAddFriendReq, &CG4GameScriptOp::DoAskAddFriendReq)
		ADD_OPMAP(TRANS_AddSeenMonsterNotify, &CG4GameScriptOp::DoAddSeenMonsterNotify)
		ADD_OPMAP(TRANS_AvatarFightPropNotify, &CG4GameScriptOp::DoAvatarFightPropNotify)
		ADD_OPMAP(TRANS_ChangeTeamNameReq, &CG4GameScriptOp::DoChangeTeamNameReq)
		ADD_OPMAP(TRANS_StoreWeightLimitNotify, &CG4GameScriptOp::DoStoreWeightLimitNotify)
		ADD_OPMAP(TRANS_DailyTaskProgressNotify, &CG4GameScriptOp::DoDailyTaskProgressNotify)
		ADD_OPMAP(TRANS_AvatarAbilityResetNotify, &CG4GameScriptOp::DoAvatarAbilityResetNotify)
		ADD_OPMAP(TRANS_PlayerEnterSceneNotify, &CG4GameScriptOp::DoPlayerEnterSceneNotify)
		ADD_OPMAP(TRANS_PlayerInvestigationTargetNotify, &CG4GameScriptOp::DoPlayerInvestigationTargetNotify)
		ADD_OPMAP(TRANS_BlossomBriefInfoNotify, &CG4GameScriptOp::DoBlossomBriefInfoNotify)
		ADD_OPMAP(TRANS_TowerDailyRewardProgressChangeNotify, &CG4GameScriptOp::DoTowerDailyRewardProgressChangeNotify)
		ADD_OPMAP(TRANS_ChallengeDataNotify, &CG4GameScriptOp::DoChallengeDataNotify)
		ADD_OPMAP(TRANS_GetShopmallShopDataReq, &CG4GameScriptOp::DoGetShopmallShopDataReq)
		ADD_OPMAP(TRANS_DungeonShowReminderNotify, &CG4GameScriptOp::DoDungeonShowReminderNotify)
		ADD_OPMAP(TRANS_WeaponPromoteReq, &CG4GameScriptOp::DoWeaponPromoteReq)
		ADD_OPMAP(TRANS_PushTipsReadFinishReq, &CG4GameScriptOp::DoPushTipsReadFinishReq)
		ADD_OPMAP(TRANS_ClientTriggerEventNotify, &CG4GameScriptOp::DoClientTriggerEventNotify)
		ADD_OPMAP(TRANS_GivingRecordNotify, &CG4GameScriptOp::DoGivingRecordNotify)
		ADD_OPMAP(TRANS_PlayerApplyEnterMpResultReq, &CG4GameScriptOp::DoPlayerApplyEnterMpResultReq)
		ADD_OPMAP(TRANS_ProudSkillChangeNotify, &CG4GameScriptOp::DoProudSkillChangeNotify)
		ADD_OPMAP(TRANS_QuestUpdateQuestVarNotify, &CG4GameScriptOp::DoQuestUpdateQuestVarNotify)
		ADD_OPMAP(TRANS_SceneDestroyEntityReq, &CG4GameScriptOp::DoSceneDestroyEntityReq)
		ADD_OPMAP(TRANS_GetAllMailReq, &CG4GameScriptOp::DoGetAllMailReq)
		ADD_OPMAP(TRANS_SetPlayerBornDataReq, &CG4GameScriptOp::DoSetPlayerBornDataReq)
		ADD_OPMAP(TRANS_DropSubfieldReq, &CG4GameScriptOp::DoDropSubfieldReq)
		ADD_OPMAP(TRANS_BattlePassMissionDelNotify, &CG4GameScriptOp::DoBattlePassMissionDelNotify)
		ADD_OPMAP(TRANS_HostPlayerNotify, &CG4GameScriptOp::DoHostPlayerNotify)
		ADD_OPMAP(TRANS_AvatarSkillInfoNotify, &CG4GameScriptOp::DoAvatarSkillInfoNotify)
		ADD_OPMAP(TRANS_WorldResinChangeNotify, &CG4GameScriptOp::DoWorldResinChangeNotify)
		ADD_OPMAP(TRANS_GetSceneAreaReq, &CG4GameScriptOp::DoGetSceneAreaReq)
		ADD_OPMAP(TRANS_ScenePlayerLocationNotify, &CG4GameScriptOp::DoScenePlayerLocationNotify)
		ADD_OPMAP(TRANS_AvatarDelNotify, &CG4GameScriptOp::DoAvatarDelNotify)
		ADD_OPMAP(TRANS_WorldDataNotify, &CG4GameScriptOp::DoWorldDataNotify)
		ADD_OPMAP(TRANS_RobotPushPlayerDataNotify, &CG4GameScriptOp::DoRobotPushPlayerDataNotify)
		ADD_OPMAP(TRANS_TowerCurLevelRecordChangeNotify, &CG4GameScriptOp::DoTowerCurLevelRecordChangeNotify)
		ADD_OPMAP(TRANS_SceneInitFinishReq, &CG4GameScriptOp::DoSceneInitFinishReq)
		ADD_OPMAP(TRANS_QuestListNotify, &CG4GameScriptOp::DoQuestListNotify)
		ADD_OPMAP(TRANS_FocusAvatarReq, &CG4GameScriptOp::DoFocusAvatarReq)
		ADD_OPMAP(TRANS_TakeMaterialDeleteReturnReq, &CG4GameScriptOp::DoTakeMaterialDeleteReturnReq)
		ADD_OPMAP(TRANS_SceneAreaUnlockNotify, &CG4GameScriptOp::DoSceneAreaUnlockNotify)
		ADD_OPMAP(TRANS_GetAuthkeyReq, &CG4GameScriptOp::DoGetAuthkeyReq)
		ADD_OPMAP(TRANS_BargainStartNotify, &CG4GameScriptOp::DoBargainStartNotify)
		ADD_OPMAP(TRANS_DungeonCandidateTeamSetReadyReq, &CG4GameScriptOp::DoDungeonCandidateTeamSetReadyReq)
		ADD_OPMAP(TRANS_SceneTeamMPDisplayCurAvatarNotify, &CG4GameScriptOp::DoSceneTeamMPDisplayCurAvatarNotify)
		ADD_OPMAP(TRANS_DungeonChallengeBeginNotify, &CG4GameScriptOp::DoDungeonChallengeBeginNotify)
		ADD_OPMAP(TRANS_EnterWorldAreaReq, &CG4GameScriptOp::DoEnterWorldAreaReq)
		ADD_OPMAP(TRANS_DungeonCandidateTeamInfoNotify, &CG4GameScriptOp::DoDungeonCandidateTeamInfoNotify)
		ADD_OPMAP(TRANS_EndCameraSceneLookNotify, &CG4GameScriptOp::DoEndCameraSceneLookNotify)
		ADD_OPMAP(TRANS_TriggerCreateGadgetToEquipPartNotify, &CG4GameScriptOp::DoTriggerCreateGadgetToEquipPartNotify)
		ADD_OPMAP(TRANS_PlayerSetLanguageReq, &CG4GameScriptOp::DoPlayerSetLanguageReq)
		ADD_OPMAP(TRANS_SceneEntityMoveNotify, &CG4GameScriptOp::DoSceneEntityMoveNotify)
		ADD_OPMAP(TRANS_ClientTransmitReq, &CG4GameScriptOp::DoClientTransmitReq)
		ADD_OPMAP(TRANS_QuestListUpdateNotify, &CG4GameScriptOp::DoQuestListUpdateNotify)
		ADD_OPMAP(TRANS_PingReq, &CG4GameScriptOp::DoPingReq)
		ADD_OPMAP(TRANS_AvatarPromoteReq, &CG4GameScriptOp::DoAvatarPromoteReq)
		ADD_OPMAP(TRANS_GetDailyDungeonEntryInfoReq, &CG4GameScriptOp::DoGetDailyDungeonEntryInfoReq)
		ADD_OPMAP(TRANS_SceneAreaWeatherNotify, &CG4GameScriptOp::DoSceneAreaWeatherNotify)
		ADD_OPMAP(TRANS_PlayerApplyEnterMpNotify, &CG4GameScriptOp::DoPlayerApplyEnterMpNotify)
		ADD_OPMAP(TRANS_BonusActivityAllDataNotify, &CG4GameScriptOp::DoBonusActivityAllDataNotify)
		ADD_OPMAP(TRANS_PlayerGameTimeNotify, &CG4GameScriptOp::DoPlayerGameTimeNotify)
		ADD_OPMAP(TRANS_ItemGivingReq, &CG4GameScriptOp::DoItemGivingReq)
		ADD_OPMAP(TRANS_QuestCreateEntityReq, &CG4GameScriptOp::DoQuestCreateEntityReq)
		ADD_OPMAP(TRANS_EvtAvatarExitFocusNotify, &CG4GameScriptOp::DoEvtAvatarExitFocusNotify)
		ADD_OPMAP(TRANS_TowerGetFloorStarRewardReq, &CG4GameScriptOp::DoTowerGetFloorStarRewardReq)
		ADD_OPMAP(TRANS_SeaLampTakeContributionRewardReq, &CG4GameScriptOp::DoSeaLampTakeContributionRewardReq)
		ADD_OPMAP(TRANS_PlayerRandomCookReq, &CG4GameScriptOp::DoPlayerRandomCookReq)
		ADD_OPMAP(TRANS_DungeonSlipRevivePointActivateReq, &CG4GameScriptOp::DoDungeonSlipRevivePointActivateReq)
		ADD_OPMAP(TRANS_LogCutsceneNotify, &CG4GameScriptOp::DoLogCutsceneNotify)
		ADD_OPMAP(TRANS_ServerAnnounceRevokeNotify, &CG4GameScriptOp::DoServerAnnounceRevokeNotify)
		ADD_OPMAP(TRANS_GetBonusActivityRewardReq, &CG4GameScriptOp::DoGetBonusActivityRewardReq)
		ADD_OPMAP(TRANS_QuestDestroyNpcReq, &CG4GameScriptOp::DoQuestDestroyNpcReq)
		ADD_OPMAP(TRANS_GMShowNavMeshReq, &CG4GameScriptOp::DoGMShowNavMeshReq)
		ADD_OPMAP(TRANS_SceneForceUnlockNotify, &CG4GameScriptOp::DoSceneForceUnlockNotify)
		ADD_OPMAP(TRANS_PlayerPreEnterMpNotify, &CG4GameScriptOp::DoPlayerPreEnterMpNotify)
		ADD_OPMAP(TRANS_DelMailReq, &CG4GameScriptOp::DoDelMailReq)
		ADD_OPMAP(TRANS_ServerLogNotify, &CG4GameScriptOp::DoServerLogNotify)
		ADD_OPMAP(TRANS_AvatarPropNotify, &CG4GameScriptOp::DoAvatarPropNotify)
		ADD_OPMAP(TRANS_MassiveEntityStateChangedNotify, &CG4GameScriptOp::DoMassiveEntityStateChangedNotify)
		ADD_OPMAP(TRANS_GetInvestigationMonsterReq, &CG4GameScriptOp::DoGetInvestigationMonsterReq)
		ADD_OPMAP(TRANS_FinishedParentQuestUpdateNotify, &CG4GameScriptOp::DoFinishedParentQuestUpdateNotify)
		ADD_OPMAP(TRANS_DungeonSettleNotify, &CG4GameScriptOp::DoDungeonSettleNotify)
		ADD_OPMAP(TRANS_EntityAuthorityChangeNotify, &CG4GameScriptOp::DoEntityAuthorityChangeNotify)
		ADD_OPMAP(TRANS_AvatarSkillUpgradeReq, &CG4GameScriptOp::DoAvatarSkillUpgradeReq)
		ADD_OPMAP(TRANS_PlayerPropChangeNotify, &CG4GameScriptOp::DoPlayerPropChangeNotify)
		ADD_OPMAP(TRANS_DungeonPlayerDieReq, &CG4GameScriptOp::DoDungeonPlayerDieReq)
		ADD_OPMAP(TRANS_AvatarExpeditionCallBackReq, &CG4GameScriptOp::DoAvatarExpeditionCallBackReq)
		ADD_OPMAP(TRANS_ExecuteGroupTriggerReq, &CG4GameScriptOp::DoExecuteGroupTriggerReq)
		ADD_OPMAP(TRANS_GetOnlinePlayerListReq, &CG4GameScriptOp::DoGetOnlinePlayerListReq)
		ADD_OPMAP(TRANS_RechargeReq, &CG4GameScriptOp::DoRechargeReq)
		ADD_OPMAP(TRANS_ChangeMpTeamAvatarReq, &CG4GameScriptOp::DoChangeMpTeamAvatarReq)
		ADD_OPMAP(TRANS_GetShopReq, &CG4GameScriptOp::DoGetShopReq)
		ADD_OPMAP(TRANS_GetPlayerFriendListReq, &CG4GameScriptOp::DoGetPlayerFriendListReq)
		ADD_OPMAP(TRANS_BuyWorldResinReq, &CG4GameScriptOp::DoBuyWorldResinReq)
		ADD_OPMAP(TRANS_SetPlayerNameReq, &CG4GameScriptOp::DoSetPlayerNameReq)
		ADD_OPMAP(TRANS_ServerDisconnectClientNotify, &CG4GameScriptOp::DoServerDisconnectClientNotify)
		ADD_OPMAP(TRANS_SeaLampContributeItemReq, &CG4GameScriptOp::DoSeaLampContributeItemReq)
		ADD_OPMAP(TRANS_SceneTimeNotify, &CG4GameScriptOp::DoSceneTimeNotify)
		ADD_OPMAP(TRANS_ScenePlayerInfoNotify, &CG4GameScriptOp::DoScenePlayerInfoNotify)
		ADD_OPMAP(TRANS_KeepAliveNotify, &CG4GameScriptOp::DoKeepAliveNotify)
		ADD_OPMAP(TRANS_EvtBeingHitsCombineNotify, &CG4GameScriptOp::DoEvtBeingHitsCombineNotify)
		ADD_OPMAP(TRANS_ClientAbilityInitFinishNotify, &CG4GameScriptOp::DoClientAbilityInitFinishNotify)
		ADD_OPMAP(TRANS_AvatarBuffAddNotify, &CG4GameScriptOp::DoAvatarBuffAddNotify)
		ADD_OPMAP(TRANS_SceneEntityMoveReq, &CG4GameScriptOp::DoSceneEntityMoveReq)
		ADD_OPMAP(TRANS_ExitTransPointRegionNotify, &CG4GameScriptOp::DoExitTransPointRegionNotify)
		ADD_OPMAP(TRANS_PlayerInvestigationAllInfoNotify, &CG4GameScriptOp::DoPlayerInvestigationAllInfoNotify)
		ADD_OPMAP(TRANS_DungeonEntryInfoReq, &CG4GameScriptOp::DoDungeonEntryInfoReq)
		ADD_OPMAP(TRANS_GetQuestTalkHistoryReq, &CG4GameScriptOp::DoGetQuestTalkHistoryReq)
		ADD_OPMAP(TRANS_SetPlayerPropReq, &CG4GameScriptOp::DoSetPlayerPropReq)
		ADD_OPMAP(TRANS_ExitSceneWeatherAreaNotify, &CG4GameScriptOp::DoExitSceneWeatherAreaNotify)
		ADD_OPMAP(TRANS_DeleteFriendReq, &CG4GameScriptOp::DoDeleteFriendReq)
		ADD_OPMAP(TRANS_MonsterSummonTagNotify, &CG4GameScriptOp::DoMonsterSummonTagNotify)
		ADD_OPMAP(TRANS_ActivityInfoNotify, &CG4GameScriptOp::DoActivityInfoNotify)
		ADD_OPMAP(TRANS_EvtCostStaminaNotify, &CG4GameScriptOp::DoEvtCostStaminaNotify)
		ADD_OPMAP(TRANS_ChatHistoryNotify, &CG4GameScriptOp::DoChatHistoryNotify)
		ADD_OPMAP(TRANS_DungeonCandidateTeamReplyInviteReq, &CG4GameScriptOp::DoDungeonCandidateTeamReplyInviteReq)
		ADD_OPMAP(TRANS_SeeMonsterReq, &CG4GameScriptOp::DoSeeMonsterReq)
		ADD_OPMAP(TRANS_SealBattleEndNotify, &CG4GameScriptOp::DoSealBattleEndNotify)
		ADD_OPMAP(TRANS_TowerBriefDataNotify, &CG4GameScriptOp::DoTowerBriefDataNotify)
		ADD_OPMAP(TRANS_ProudSkillExtraLevelNotify, &CG4GameScriptOp::DoProudSkillExtraLevelNotify)
		ADD_OPMAP(TRANS_PersonalSceneJumpReq, &CG4GameScriptOp::DoPersonalSceneJumpReq)
		ADD_OPMAP(TRANS_PlayerEnterSceneInfoNotify, &CG4GameScriptOp::DoPlayerEnterSceneInfoNotify)
		ADD_OPMAP(TRANS_AbilityInvocationFixedNotify, &CG4GameScriptOp::DoAbilityInvocationFixedNotify)
		ADD_OPMAP(TRANS_ClientReconnectNotify, &CG4GameScriptOp::DoClientReconnectNotify)
		ADD_OPMAP(TRANS_AvatarSkillDepotChangeNotify, &CG4GameScriptOp::DoAvatarSkillDepotChangeNotify)
		ADD_OPMAP(TRANS_SceneGetAreaExplorePercentReq, &CG4GameScriptOp::DoSceneGetAreaExplorePercentReq)
		ADD_OPMAP(TRANS_EvtAnimatorParameterNotify, &CG4GameScriptOp::DoEvtAnimatorParameterNotify)
		ADD_OPMAP(TRANS_LoadActivityTerrainNotify, &CG4GameScriptOp::DoLoadActivityTerrainNotify)
		ADD_OPMAP(TRANS_DungeonDataNotify, &CG4GameScriptOp::DoDungeonDataNotify)
		ADD_OPMAP(TRANS_GetScenePointReq, &CG4GameScriptOp::DoGetScenePointReq)
		ADD_OPMAP(TRANS_SeaLampTakePhaseRewardReq, &CG4GameScriptOp::DoSeaLampTakePhaseRewardReq)
		ADD_OPMAP(TRANS_UnlockAvatarTalentReq, &CG4GameScriptOp::DoUnlockAvatarTalentReq)
		ADD_OPMAP(TRANS_GadgetStateNotify, &CG4GameScriptOp::DoGadgetStateNotify)
		ADD_OPMAP(TRANS_AvatarUpgradeReq, &CG4GameScriptOp::DoAvatarUpgradeReq)
		ADD_OPMAP(TRANS_EvtFaceToDirNotify, &CG4GameScriptOp::DoEvtFaceToDirNotify)
		ADD_OPMAP(TRANS_DungeonGetStatueDropReq, &CG4GameScriptOp::DoDungeonGetStatueDropReq)
		ADD_OPMAP(TRANS_PlatformStartRouteNotify, &CG4GameScriptOp::DoPlatformStartRouteNotify)
		ADD_OPMAP(TRANS_GadgetInteractReq, &CG4GameScriptOp::DoGadgetInteractReq)
		ADD_OPMAP(TRANS_DailyTaskScoreRewardNotify, &CG4GameScriptOp::DoDailyTaskScoreRewardNotify)
		ADD_OPMAP(TRANS_EntityPropNotify, &CG4GameScriptOp::DoEntityPropNotify)
		ADD_OPMAP(TRANS_SceneWeatherForcastReq, &CG4GameScriptOp::DoSceneWeatherForcastReq)
		ADD_OPMAP(TRANS_MailChangeNotify, &CG4GameScriptOp::DoMailChangeNotify)
		ADD_OPMAP(TRANS_GetActivityInfoReq, &CG4GameScriptOp::DoGetActivityInfoReq)
		ADD_OPMAP(TRANS_EvtFaceToEntityNotify, &CG4GameScriptOp::DoEvtFaceToEntityNotify)
		ADD_OPMAP(TRANS_ChapterStateNotify, &CG4GameScriptOp::DoChapterStateNotify)
		ADD_OPMAP(TRANS_PlayerChatReq, &CG4GameScriptOp::DoPlayerChatReq)
		ADD_OPMAP(TRANS_BossChestActivateNotify, &CG4GameScriptOp::DoBossChestActivateNotify)
		ADD_OPMAP(TRANS_TowerSurrenderReq, &CG4GameScriptOp::DoTowerSurrenderReq)
		ADD_OPMAP(TRANS_EvtAvatarUpdateFocusNotify, &CG4GameScriptOp::DoEvtAvatarUpdateFocusNotify)
		ADD_OPMAP(TRANS_ClientReportNotify, &CG4GameScriptOp::DoClientReportNotify)
		ADD_OPMAP(TRANS_PlayerTimeNotify, &CG4GameScriptOp::DoPlayerTimeNotify)
		ADD_OPMAP(TRANS_AbilityInvocationFailNotify, &CG4GameScriptOp::DoAbilityInvocationFailNotify)
		ADD_OPMAP(TRANS_ReliquaryUpgradeReq, &CG4GameScriptOp::DoReliquaryUpgradeReq)
		ADD_OPMAP(TRANS_SignInAllDataNotify, &CG4GameScriptOp::DoSignInAllDataNotify)
		ADD_OPMAP(TRANS_DataResVersionNotify, &CG4GameScriptOp::DoDataResVersionNotify)
		ADD_OPMAP(TRANS_DelTeamEntityNotify, &CG4GameScriptOp::DoDelTeamEntityNotify)
		ADD_OPMAP(TRANS_ProudSkillUpgradeReq, &CG4GameScriptOp::DoProudSkillUpgradeReq)
		ADD_OPMAP(TRANS_AvatarExpeditionGetRewardReq, &CG4GameScriptOp::DoAvatarExpeditionGetRewardReq)
		ADD_OPMAP(TRANS_AvatarDieAnimationEndReq, &CG4GameScriptOp::DoAvatarDieAnimationEndReq)
		ADD_OPMAP(TRANS_GetSceneNpcPositionReq, &CG4GameScriptOp::DoGetSceneNpcPositionReq)
		ADD_OPMAP(TRANS_DropHintNotify, &CG4GameScriptOp::DoDropHintNotify)
		ADD_OPMAP(TRANS_CompoundDataNotify, &CG4GameScriptOp::DoCompoundDataNotify)
		//auto created code end
	REGISTERSCRIPTOP_END()
};
#endif
