#ifndef _GAME_PKGPROCESS_H_
#define _GAME_PKGPROCESS_H_
#include "ProtocolCode.h"
#include "pkgprocess_t.h"
#include "pack_i.h"
#include <google/protobuf/service.h>
#include <google/protobuf/util/json_util.h>
#include "define.pb.h"
#include "Hk4eProto.h"
//#include "player.pb.h"
#include "packet.h"

/*
收包处理类，需实现以下功能

1. 将Pack.cpp 中 UnpackMsg 函数传入的buffer进行解包，解出是哪条消息与msgID。在StoreProtocolID函数中返回该消息ID。
2. 通过宏ADD_HANDLERMAP将消息ID绑定到包处理函数，
3. 在所绑定的函数中实现收包处理。

只需满足上述需求，类实现可任意，为简单起见，提供如下模板

*/

class CG4GameProcess: public TPkgProcess<CG4GameProcess>
{
public:
    CG4GameProcess();
    ~CG4GameProcess();
    virtual int GetHeaderLen();
	/*
	描述：解包函数，获取消息的MSGID
	参数说明
	[IN] dwUin:机器人编号
	[IN] pPkg: Pack.cpp UnpackMsg 函数所传入的待解包的buffer
	[IN] uPkgSize: Pack.cpp UnpackMsg 函数所返回的待解包buffer的长度
	*/
	virtual unsigned StoreProtocolID(unsigned dwUin, void *pPkg, size_t uPkgSize);
	//no need to auto create
	google::protobuf::util::JsonPrintOptions option;
	const char * GetCurDateTimeCStr(struct timeval *pstNowTime);
private:
	/*
	描述：具体收包处理函数
	参数说明
	[IN] dwUin:机器人编号
	[IN] pPkg: Pack.cpp UnpackMsg 函数所传入的待解包的buffer
	[IN] uPkgSize: Pack.cpp UnpackMsg 函数所返回的待解包buffer的长度
	[OUT] nErrorCode: 出错时的错误码，填值后会中断收包流程
	[RTN] =0：收包成功， <0：收包失败，中断收包流程。
	*/
	//auto created code start
	int OnEntityFightPropChangeReasonNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSetUpAvatarTeamRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetPlayerFriendListRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerPropNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnUnfreezeGroupLimitNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnBeginCameraSceneLookNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnShowMessageNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEvtAvatarSitDownNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnLevelupCityRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerLevelRewardUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnBargainTerminateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEvtCreateGadgetNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarEquipChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnTowerBuffSelectRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnMaterialDeleteReturnNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneForceLockNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDoGachaRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonCandidateTeamReplyInviteRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSyncTeamEntityNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnMarkEntityInMinMapNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnExecuteGroupTriggerRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnForgeStartRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetDungeonEntryExploreConditionRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEvtBeingHitNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnQuestCreateEntityRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnBuyWorldResinRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSetPlayerNameRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnStoreItemChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarPropChangeReasonNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnTowerFloorRecordChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEnterWorldFogAreaNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSeaLampFlyLampRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnChallengeRecordNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerLogoutNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlatformStopRouteNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSetEntityClientDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerQuitDungeonRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPathfindingEnterSceneRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnWorldOwnerBlossomScheduleInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetMailItemRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPushTipsAllDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonCandidateTeamLeaveRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEnterSceneWeatherAreaNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGMShowObstacleRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneEntitiesMovesRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnWatcherAllDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEvtBulletMoveNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnReliquaryPromoteRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerInvestigationNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnItemAddHintNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnRechargeRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnBackMyWorldRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnForgeQueueDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnChangeMpTeamAvatarRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnUnlockWorldFogAreaNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnBuyGoodsRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAddRandTaskInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSpringUseRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarLifeStateChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonCandidateTeamChangeAvatarRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnCreateMassiveEntityRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPathfindingPingNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarExpeditionGetRewardRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarFightPropUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetPushTipsRewardRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnChooseCurAvatarTeamRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnLogTalkNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDoSetPlayerBornDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonCandidateTeamPlayerLeaveNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlatformChangeRouteNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDailyTaskDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEvtSetAttackTargetNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnHitClientTrivialNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonDieOptionRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnTowerSurrenderRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetPlayerSocialDetailRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneTransToPointRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonChallengeFinishNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnQuestProgressUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneGetAreaExplorePercentRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEntityJumpNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSealBattleProgressNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSignInInfoRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnJoinPlayerFailNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnClientScriptEventNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGivingRecordChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnUnlockTransPointRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnClientAbilityInitBeginNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerApplyEnterMpRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnServerTimeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnClientAbilitiesInitFinishCombineNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnWorldPlayerLocationNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnTowerAllDataRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSetPlayerSignatureRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonCandidateTeamRefuseNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonWayPointNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerChatNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEvtAnimatorStateChangedNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSetOpenStateRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnTakeInvestigationTargetRewardRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnWorldPlayerInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnQuestDestroyEntityRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnCookDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnMonsterForceAlertNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAllMarkPointNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnTowerMiddleLevelChangeTeamNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneKickPlayerNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneEntitiesMoveCombineNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnOpenStateChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnTowerDailyRewardProgressChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnBargainOfferPriceRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnTakeInvestigationRewardRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnFinishedParentQuestNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnBuyResinRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnMonsterAlertChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnResinChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerPropChangeReasonNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarBuffDelNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSeaLampTakeContributionRewardRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSignInInfoOpenNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnCutSceneFinishNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetCompoundDataRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnExitSceneWeatherAreaNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnCutSceneBeginNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEvtDestroyGadgetNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarDieAnimationEndRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnClientPauseNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGrantRewardNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneEntityDisappearNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonPlayerDieNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneAreaExploreNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarAbilityResetFinishNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnTakeoffEquipRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneEntityDrownRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSetPlayerHeadImageRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnBonusActivityUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEvtAiSyncSkillCdNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonCandidateTeamDismissNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnActivityPlayOpenAnimNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnTakeCompoundOutputRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGMShowNavMeshRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEvtAvatarStandUpNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetInvestigationMonsterRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerStoreNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetPlayerTokenRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonEntryToBeExploreNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnBattlePassAllDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEvtRushMoveNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEnterScenePeerNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnMaterialDeleteUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEntityFightPropNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnTakeBattlePassRewardRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarExpeditionDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerCookRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnWatcherEventTypeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonCandidateTeamInviteRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEvtEntityRenderersChangedNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnWorktopOptionNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetSignInRewardRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarFetterDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSetSceneWeatherAreaRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnChangeAvatarRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAddQuestContentProgressRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnLeaveSceneRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnScenePointUnlockNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnWorldOwnerDailyTaskNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneEntityAppearNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnWeaponAwakenRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarTeamUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonCandidateTeamCreateRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnWeaponPromoteRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneKickPlayerRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDestroyMassiveEntityNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPostEnterSceneRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetShopmallDataRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEnterSceneReadyRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneTeamUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnCookGradeDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnRefreshBackgroundAvatarRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnScenePlayerSoundNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEvtBulletDeactiveNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonWayPointActivateRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEnterTransPointRegionNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerCookArgsRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnBlossomChestInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerApplyEnterMpResultRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnBattlePassCurScheduleUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnClientNewMailNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEvtEntityStartDieEndNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnQuestDelNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnItemCdGroupTimeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnBattlePassMissionUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerLoginRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnCreateMassiveEntityNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnCombineRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSealBattleBeginNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAllSeenMonsterNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnWeaponUpgradeRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAnimatorForceSetAirMoveNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarUnlockTalentNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneCreateEntityRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnWatcherEventNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnNpcTalkRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAbilityInvocationsNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlatformRouteStateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEntityFightPropUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerLuaShellNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnQuestDestroyNpcRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneRouteChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEntityMoveRoomNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnTowerLevelEndNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerEnterDungeonRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneDestroyEntityRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnLifeStateChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnRemoveRandTaskInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnActivityScheduleInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnServerBuffChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnReadMailNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnWindSeedClientNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEvtDoSkillSuccNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerApplyEnterMpResultNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerChatCDNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonCandidateTeamInviteNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnUnmarkEntityInMinMapNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnCanUseSkillNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetAuthkeyRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnChangeTeamNameRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonCandidateTeamSetReadyRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnServerAnnounceNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarExpeditionStartRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnTowerLevelStarCondNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEvtAvatarEnterFocusNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnCutSceneEndNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonFollowNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPushTipsChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarAddNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnWatcherChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarSkillMaxChargeCountNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetBlossomBriefInfoListRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetActivityScheduleRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEvtBulletHitNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEvtAiSyncCombatThreatInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnWorldOwnerBlossomBriefInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPushTipsReadFinishRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnOrderFinishNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnCombatInvocationsNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnOpenStateUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnWorldPlayerDieNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDealAddFriendRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarEnterElementViewNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarSkillChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEntityPropNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonPlayerDieRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnFocusAvatarRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDropItemRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnBuyShopmallGoodsRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAddSeenMonsterNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarFightPropNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerInvestigationAllInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnTowerEnterLevelRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnStoreWeightLimitNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDailyTaskProgressNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarAbilityResetNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerEnterSceneNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerInvestigationTargetNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSelectWorktopOptionRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnTakePlayerLevelRewardRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnMarkNewNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetPlayerMpModeAvailabilityRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnChallengeDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonShowReminderNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneAvatarStaminaStepRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnClientTriggerEventNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGivingRecordNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnProudSkillChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnQuestUpdateQuestVarNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetGachaInfoRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonGetStatueDropRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnBattlePassMissionDelNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnHostPlayerNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarSkillInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerCompoundMaterialRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnWorldResinChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnScenePlayerLocationNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarDelNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnWorldDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnRobotPushPlayerDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnTowerCurLevelRecordChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonSlipRevivePointActivateRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnUnlockAvatarTalentRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarUpgradeRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnQuestListNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneAreaUnlockNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetAllMailRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDropSubfieldRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnBargainStartNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnForgeQueueManipulateRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnUseItemRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnObstacleModifyNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnItemGivingRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnMarkMapRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneTeamMPDisplayCurAvatarNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonChallengeBeginNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPersonalSceneJumpRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonCandidateTeamInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEndCameraSceneLookNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnTriggerCreateGadgetToEquipPartNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarExpeditionAllDataRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneEntityMoveNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnBonusActivityInfoRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnWearEquipRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnExecuteGadgetLuaRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnQuestListUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarExpeditionCallBackRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneAreaWeatherNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSetPlayerBornDataRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnCookRecipeDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarSkillUpgradeRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerApplyEnterMpNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnBonusActivityAllDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerGameTimeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEvtAvatarExitFocusNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEnterSceneDoneRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnClientTransmitRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnBigTalentPointConvertRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneWeatherForcastRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnTakeMaterialDeleteReturnRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetOnlinePlayerListRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneEntityMoveRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnLogCutsceneNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnServerAnnounceRevokeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonEntryInfoRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEnterWorldAreaRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDelMailRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAskAddFriendRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerQuitFromMpNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGmTalkRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneForceUnlockNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSeaLampContributeItemRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerPreEnterMpNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSeeMonsterRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnServerLogNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarPropNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetShopmallShopDataRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSetPlayerPropRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonCandidateTeamKickRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnMassiveEntityStateChangedNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerSetLanguageRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnFinishedParentQuestUpdateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnTowerGetFloorStarRewardRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonSettleNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEntityAuthorityChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSignInAllDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerPropChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPingRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnStoreItemDelNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnTakeBattlePassMissionPointRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEntityForceSyncRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetScenePointRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnElementReactionLogNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSeaLampTakePhaseRewardRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGadgetInteractRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnServerDisconnectClientNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneTimeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnScenePlayerInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnKeepAliveNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEvtBeingHitsCombineNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnClientAbilityInitFinishNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarBuffAddNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDungeonDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnExitTransPointRegionNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarPromoteRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnClientFpsStatusNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerChatRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnQuestUpdateQuestVarRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnTowerTeamSelectRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnMonsterSummonTagNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnActivityInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSetPlayerBirthdayRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEvtCostStaminaNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnChatHistoryNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnQueryPathRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerLogoutRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSealBattleEndNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnChangeGameTimeRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnTowerBriefDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnProudSkillExtraLevelNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerEnterSceneInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAbilityInvocationFixedNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnClientReconnectNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarSkillDepotChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetSceneAreaRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEvtAnimatorParameterNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnLoadActivityTerrainNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnReliquaryUpgradeRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDeleteFriendRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnProudSkillUpgradeRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnSceneInitFinishRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGadgetStateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnLockWorldFogAreaNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEvtFaceToDirNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetQuestTalkHistoryRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarCardChangeRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlatformStartRouteNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnBlossomBriefInfoNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetShopRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDailyTaskScoreRewardNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetDailyDungeonEntryInfoRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAvatarChangeElementTypeRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetSceneNpcPositionRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerRandomCookRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnForgeGetQueueDataRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnMailChangeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEvtFaceToEntityNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnChapterStateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnWorldPlayerReviveRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnBossChestActivateNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnJoinPlayerSceneRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnEvtAvatarUpdateFocusNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnClientReportNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerTimeNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnAbilityInvocationFailNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDataResVersionNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnPlayerSetPauseRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDelTeamEntityNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetActivityInfoRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnGetBonusActivityRewardRsp(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnDropHintNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	int OnCompoundDataNotify(unsigned dwUin, void *pPkg, size_t uPkgSize, int &nErrorCode);
	//auto created code end

private:
	REGISTERHANDLER_BEGIN(init)
		//根据消息类型注册消息处理回调函数
		//no need to auto create^M
		//ADD_HANDLERMAP(proto::QueryRegionListHttpRsp_CmdId_CMD_ID,      &CG4GameProcess::OnQueryRegionListHttpRsp)
		//ADD_HANDLERMAP(proto::QueryCurrRegionHttpRsp_CmdId_CMD_ID,      &CG4GameProcess::OnQueryCurrRegionHttpRsp)
		//auto created code start
		ADD_HANDLERMAP(proto::EntityFightPropChangeReasonNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEntityFightPropChangeReasonNotify)
		ADD_HANDLERMAP(proto::SetUpAvatarTeamRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSetUpAvatarTeamRsp)
		ADD_HANDLERMAP(proto::GetPlayerFriendListRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetPlayerFriendListRsp)
		ADD_HANDLERMAP(proto::PlayerPropNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerPropNotify)
		ADD_HANDLERMAP(proto::UnfreezeGroupLimitNotify_CmdId_CMD_ID,	&CG4GameProcess::OnUnfreezeGroupLimitNotify)
		ADD_HANDLERMAP(proto::BeginCameraSceneLookNotify_CmdId_CMD_ID,	&CG4GameProcess::OnBeginCameraSceneLookNotify)
		ADD_HANDLERMAP(proto::AvatarDataNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarDataNotify)
		ADD_HANDLERMAP(proto::ShowMessageNotify_CmdId_CMD_ID,	&CG4GameProcess::OnShowMessageNotify)
		ADD_HANDLERMAP(proto::EvtAvatarSitDownNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEvtAvatarSitDownNotify)
		ADD_HANDLERMAP(proto::LevelupCityRsp_CmdId_CMD_ID,	&CG4GameProcess::OnLevelupCityRsp)
		ADD_HANDLERMAP(proto::PlayerLevelRewardUpdateNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerLevelRewardUpdateNotify)
		ADD_HANDLERMAP(proto::BargainTerminateNotify_CmdId_CMD_ID,	&CG4GameProcess::OnBargainTerminateNotify)
		ADD_HANDLERMAP(proto::EvtCreateGadgetNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEvtCreateGadgetNotify)
		ADD_HANDLERMAP(proto::AvatarEquipChangeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarEquipChangeNotify)
		ADD_HANDLERMAP(proto::TowerBuffSelectRsp_CmdId_CMD_ID,	&CG4GameProcess::OnTowerBuffSelectRsp)
		ADD_HANDLERMAP(proto::MaterialDeleteReturnNotify_CmdId_CMD_ID,	&CG4GameProcess::OnMaterialDeleteReturnNotify)
		ADD_HANDLERMAP(proto::SceneForceLockNotify_CmdId_CMD_ID,	&CG4GameProcess::OnSceneForceLockNotify)
		ADD_HANDLERMAP(proto::DoGachaRsp_CmdId_CMD_ID,	&CG4GameProcess::OnDoGachaRsp)
		ADD_HANDLERMAP(proto::DungeonCandidateTeamReplyInviteRsp_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonCandidateTeamReplyInviteRsp)
		ADD_HANDLERMAP(proto::SyncTeamEntityNotify_CmdId_CMD_ID,	&CG4GameProcess::OnSyncTeamEntityNotify)
		ADD_HANDLERMAP(proto::MarkEntityInMinMapNotify_CmdId_CMD_ID,	&CG4GameProcess::OnMarkEntityInMinMapNotify)
		ADD_HANDLERMAP(proto::ExecuteGroupTriggerRsp_CmdId_CMD_ID,	&CG4GameProcess::OnExecuteGroupTriggerRsp)
		ADD_HANDLERMAP(proto::ForgeStartRsp_CmdId_CMD_ID,	&CG4GameProcess::OnForgeStartRsp)
		ADD_HANDLERMAP(proto::GetDungeonEntryExploreConditionRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetDungeonEntryExploreConditionRsp)
		ADD_HANDLERMAP(proto::EvtBeingHitNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEvtBeingHitNotify)
		ADD_HANDLERMAP(proto::QuestCreateEntityRsp_CmdId_CMD_ID,	&CG4GameProcess::OnQuestCreateEntityRsp)
		ADD_HANDLERMAP(proto::BuyWorldResinRsp_CmdId_CMD_ID,	&CG4GameProcess::OnBuyWorldResinRsp)
		ADD_HANDLERMAP(proto::SetPlayerNameRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSetPlayerNameRsp)
		ADD_HANDLERMAP(proto::StoreItemChangeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnStoreItemChangeNotify)
		ADD_HANDLERMAP(proto::AvatarPropChangeReasonNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarPropChangeReasonNotify)
		ADD_HANDLERMAP(proto::TowerFloorRecordChangeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnTowerFloorRecordChangeNotify)
		ADD_HANDLERMAP(proto::EnterWorldFogAreaNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEnterWorldFogAreaNotify)
		ADD_HANDLERMAP(proto::SeaLampFlyLampRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSeaLampFlyLampRsp)
		ADD_HANDLERMAP(proto::ChallengeRecordNotify_CmdId_CMD_ID,	&CG4GameProcess::OnChallengeRecordNotify)
		ADD_HANDLERMAP(proto::PlayerLogoutNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerLogoutNotify)
		ADD_HANDLERMAP(proto::PlatformStopRouteNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlatformStopRouteNotify)
		ADD_HANDLERMAP(proto::SetEntityClientDataNotify_CmdId_CMD_ID,	&CG4GameProcess::OnSetEntityClientDataNotify)
		ADD_HANDLERMAP(proto::PlayerQuitDungeonRsp_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerQuitDungeonRsp)
		ADD_HANDLERMAP(proto::PathfindingEnterSceneRsp_CmdId_CMD_ID,	&CG4GameProcess::OnPathfindingEnterSceneRsp)
		ADD_HANDLERMAP(proto::WorldOwnerBlossomScheduleInfoNotify_CmdId_CMD_ID,	&CG4GameProcess::OnWorldOwnerBlossomScheduleInfoNotify)
		ADD_HANDLERMAP(proto::GetMailItemRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetMailItemRsp)
		ADD_HANDLERMAP(proto::PushTipsAllDataNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPushTipsAllDataNotify)
		ADD_HANDLERMAP(proto::DungeonCandidateTeamLeaveRsp_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonCandidateTeamLeaveRsp)
		ADD_HANDLERMAP(proto::EnterSceneWeatherAreaNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEnterSceneWeatherAreaNotify)
		ADD_HANDLERMAP(proto::GMShowObstacleRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGMShowObstacleRsp)
		ADD_HANDLERMAP(proto::SceneEntitiesMovesRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSceneEntitiesMovesRsp)
		ADD_HANDLERMAP(proto::WatcherAllDataNotify_CmdId_CMD_ID,	&CG4GameProcess::OnWatcherAllDataNotify)
		ADD_HANDLERMAP(proto::EvtBulletMoveNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEvtBulletMoveNotify)
		ADD_HANDLERMAP(proto::ReliquaryPromoteRsp_CmdId_CMD_ID,	&CG4GameProcess::OnReliquaryPromoteRsp)
		ADD_HANDLERMAP(proto::PlayerInvestigationNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerInvestigationNotify)
		ADD_HANDLERMAP(proto::ItemAddHintNotify_CmdId_CMD_ID,	&CG4GameProcess::OnItemAddHintNotify)
		ADD_HANDLERMAP(proto::RechargeRsp_CmdId_CMD_ID,	&CG4GameProcess::OnRechargeRsp)
		ADD_HANDLERMAP(proto::BackMyWorldRsp_CmdId_CMD_ID,	&CG4GameProcess::OnBackMyWorldRsp)
		ADD_HANDLERMAP(proto::ForgeQueueDataNotify_CmdId_CMD_ID,	&CG4GameProcess::OnForgeQueueDataNotify)
		ADD_HANDLERMAP(proto::ChangeMpTeamAvatarRsp_CmdId_CMD_ID,	&CG4GameProcess::OnChangeMpTeamAvatarRsp)
		ADD_HANDLERMAP(proto::UnlockWorldFogAreaNotify_CmdId_CMD_ID,	&CG4GameProcess::OnUnlockWorldFogAreaNotify)
		ADD_HANDLERMAP(proto::BuyGoodsRsp_CmdId_CMD_ID,	&CG4GameProcess::OnBuyGoodsRsp)
		ADD_HANDLERMAP(proto::AddRandTaskInfoNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAddRandTaskInfoNotify)
		ADD_HANDLERMAP(proto::SpringUseRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSpringUseRsp)
		ADD_HANDLERMAP(proto::AvatarLifeStateChangeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarLifeStateChangeNotify)
		ADD_HANDLERMAP(proto::DungeonCandidateTeamChangeAvatarRsp_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonCandidateTeamChangeAvatarRsp)
		ADD_HANDLERMAP(proto::CreateMassiveEntityRsp_CmdId_CMD_ID,	&CG4GameProcess::OnCreateMassiveEntityRsp)
		ADD_HANDLERMAP(proto::PathfindingPingNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPathfindingPingNotify)
		ADD_HANDLERMAP(proto::AvatarExpeditionGetRewardRsp_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarExpeditionGetRewardRsp)
		ADD_HANDLERMAP(proto::AvatarFightPropUpdateNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarFightPropUpdateNotify)
		ADD_HANDLERMAP(proto::GetPushTipsRewardRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetPushTipsRewardRsp)
		ADD_HANDLERMAP(proto::ChooseCurAvatarTeamRsp_CmdId_CMD_ID,	&CG4GameProcess::OnChooseCurAvatarTeamRsp)
		ADD_HANDLERMAP(proto::LogTalkNotify_CmdId_CMD_ID,	&CG4GameProcess::OnLogTalkNotify)
		ADD_HANDLERMAP(proto::DoSetPlayerBornDataNotify_CmdId_CMD_ID,	&CG4GameProcess::OnDoSetPlayerBornDataNotify)
		ADD_HANDLERMAP(proto::DungeonCandidateTeamPlayerLeaveNotify_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonCandidateTeamPlayerLeaveNotify)
		ADD_HANDLERMAP(proto::PlatformChangeRouteNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlatformChangeRouteNotify)
		ADD_HANDLERMAP(proto::DailyTaskDataNotify_CmdId_CMD_ID,	&CG4GameProcess::OnDailyTaskDataNotify)
		ADD_HANDLERMAP(proto::EvtSetAttackTargetNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEvtSetAttackTargetNotify)
		ADD_HANDLERMAP(proto::HitClientTrivialNotify_CmdId_CMD_ID,	&CG4GameProcess::OnHitClientTrivialNotify)
		ADD_HANDLERMAP(proto::DungeonDieOptionRsp_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonDieOptionRsp)
		ADD_HANDLERMAP(proto::TowerSurrenderRsp_CmdId_CMD_ID,	&CG4GameProcess::OnTowerSurrenderRsp)
		ADD_HANDLERMAP(proto::GetPlayerSocialDetailRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetPlayerSocialDetailRsp)
		ADD_HANDLERMAP(proto::SceneTransToPointRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSceneTransToPointRsp)
		ADD_HANDLERMAP(proto::DungeonChallengeFinishNotify_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonChallengeFinishNotify)
		ADD_HANDLERMAP(proto::QuestProgressUpdateNotify_CmdId_CMD_ID,	&CG4GameProcess::OnQuestProgressUpdateNotify)
		ADD_HANDLERMAP(proto::SceneGetAreaExplorePercentRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSceneGetAreaExplorePercentRsp)
		ADD_HANDLERMAP(proto::EntityJumpNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEntityJumpNotify)
		ADD_HANDLERMAP(proto::SealBattleProgressNotify_CmdId_CMD_ID,	&CG4GameProcess::OnSealBattleProgressNotify)
		ADD_HANDLERMAP(proto::SignInInfoRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSignInInfoRsp)
		ADD_HANDLERMAP(proto::JoinPlayerFailNotify_CmdId_CMD_ID,	&CG4GameProcess::OnJoinPlayerFailNotify)
		ADD_HANDLERMAP(proto::ClientScriptEventNotify_CmdId_CMD_ID,	&CG4GameProcess::OnClientScriptEventNotify)
		ADD_HANDLERMAP(proto::GivingRecordChangeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnGivingRecordChangeNotify)
		ADD_HANDLERMAP(proto::UnlockTransPointRsp_CmdId_CMD_ID,	&CG4GameProcess::OnUnlockTransPointRsp)
		ADD_HANDLERMAP(proto::ClientAbilityInitBeginNotify_CmdId_CMD_ID,	&CG4GameProcess::OnClientAbilityInitBeginNotify)
		ADD_HANDLERMAP(proto::PlayerApplyEnterMpRsp_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerApplyEnterMpRsp)
		ADD_HANDLERMAP(proto::ServerTimeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnServerTimeNotify)
		ADD_HANDLERMAP(proto::ClientAbilitiesInitFinishCombineNotify_CmdId_CMD_ID,	&CG4GameProcess::OnClientAbilitiesInitFinishCombineNotify)
		ADD_HANDLERMAP(proto::WorldPlayerLocationNotify_CmdId_CMD_ID,	&CG4GameProcess::OnWorldPlayerLocationNotify)
		ADD_HANDLERMAP(proto::TowerAllDataRsp_CmdId_CMD_ID,	&CG4GameProcess::OnTowerAllDataRsp)
		ADD_HANDLERMAP(proto::SetPlayerSignatureRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSetPlayerSignatureRsp)
		ADD_HANDLERMAP(proto::PlayerDataNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerDataNotify)
		ADD_HANDLERMAP(proto::DungeonCandidateTeamRefuseNotify_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonCandidateTeamRefuseNotify)
		ADD_HANDLERMAP(proto::DungeonWayPointNotify_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonWayPointNotify)
		ADD_HANDLERMAP(proto::PlayerChatNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerChatNotify)
		ADD_HANDLERMAP(proto::EvtAnimatorStateChangedNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEvtAnimatorStateChangedNotify)
		ADD_HANDLERMAP(proto::SetOpenStateRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSetOpenStateRsp)
		ADD_HANDLERMAP(proto::TakeInvestigationTargetRewardRsp_CmdId_CMD_ID,	&CG4GameProcess::OnTakeInvestigationTargetRewardRsp)
		ADD_HANDLERMAP(proto::WorldPlayerInfoNotify_CmdId_CMD_ID,	&CG4GameProcess::OnWorldPlayerInfoNotify)
		ADD_HANDLERMAP(proto::QuestDestroyEntityRsp_CmdId_CMD_ID,	&CG4GameProcess::OnQuestDestroyEntityRsp)
		ADD_HANDLERMAP(proto::CookDataNotify_CmdId_CMD_ID,	&CG4GameProcess::OnCookDataNotify)
		ADD_HANDLERMAP(proto::MonsterForceAlertNotify_CmdId_CMD_ID,	&CG4GameProcess::OnMonsterForceAlertNotify)
		ADD_HANDLERMAP(proto::AllMarkPointNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAllMarkPointNotify)
		ADD_HANDLERMAP(proto::TowerMiddleLevelChangeTeamNotify_CmdId_CMD_ID,	&CG4GameProcess::OnTowerMiddleLevelChangeTeamNotify)
		ADD_HANDLERMAP(proto::SceneKickPlayerNotify_CmdId_CMD_ID,	&CG4GameProcess::OnSceneKickPlayerNotify)
		ADD_HANDLERMAP(proto::SceneEntitiesMoveCombineNotify_CmdId_CMD_ID,	&CG4GameProcess::OnSceneEntitiesMoveCombineNotify)
		ADD_HANDLERMAP(proto::OpenStateChangeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnOpenStateChangeNotify)
		ADD_HANDLERMAP(proto::TowerDailyRewardProgressChangeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnTowerDailyRewardProgressChangeNotify)
		ADD_HANDLERMAP(proto::BargainOfferPriceRsp_CmdId_CMD_ID,	&CG4GameProcess::OnBargainOfferPriceRsp)
		ADD_HANDLERMAP(proto::TakeInvestigationRewardRsp_CmdId_CMD_ID,	&CG4GameProcess::OnTakeInvestigationRewardRsp)
		ADD_HANDLERMAP(proto::FinishedParentQuestNotify_CmdId_CMD_ID,	&CG4GameProcess::OnFinishedParentQuestNotify)
		ADD_HANDLERMAP(proto::BuyResinRsp_CmdId_CMD_ID,	&CG4GameProcess::OnBuyResinRsp)
		ADD_HANDLERMAP(proto::MonsterAlertChangeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnMonsterAlertChangeNotify)
		ADD_HANDLERMAP(proto::ResinChangeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnResinChangeNotify)
		ADD_HANDLERMAP(proto::PlayerPropChangeReasonNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerPropChangeReasonNotify)
		ADD_HANDLERMAP(proto::AvatarBuffDelNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarBuffDelNotify)
		ADD_HANDLERMAP(proto::SeaLampTakeContributionRewardRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSeaLampTakeContributionRewardRsp)
		ADD_HANDLERMAP(proto::SignInInfoOpenNotify_CmdId_CMD_ID,	&CG4GameProcess::OnSignInInfoOpenNotify)
		ADD_HANDLERMAP(proto::CutSceneFinishNotify_CmdId_CMD_ID,	&CG4GameProcess::OnCutSceneFinishNotify)
		ADD_HANDLERMAP(proto::GetCompoundDataRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetCompoundDataRsp)
		ADD_HANDLERMAP(proto::SceneDataNotify_CmdId_CMD_ID,	&CG4GameProcess::OnSceneDataNotify)
		ADD_HANDLERMAP(proto::ExitSceneWeatherAreaNotify_CmdId_CMD_ID,	&CG4GameProcess::OnExitSceneWeatherAreaNotify)
		ADD_HANDLERMAP(proto::CutSceneBeginNotify_CmdId_CMD_ID,	&CG4GameProcess::OnCutSceneBeginNotify)
		ADD_HANDLERMAP(proto::EvtDestroyGadgetNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEvtDestroyGadgetNotify)
		ADD_HANDLERMAP(proto::AvatarDieAnimationEndRsp_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarDieAnimationEndRsp)
		ADD_HANDLERMAP(proto::ClientPauseNotify_CmdId_CMD_ID,	&CG4GameProcess::OnClientPauseNotify)
		ADD_HANDLERMAP(proto::GrantRewardNotify_CmdId_CMD_ID,	&CG4GameProcess::OnGrantRewardNotify)
		ADD_HANDLERMAP(proto::SceneEntityDisappearNotify_CmdId_CMD_ID,	&CG4GameProcess::OnSceneEntityDisappearNotify)
		ADD_HANDLERMAP(proto::DungeonPlayerDieNotify_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonPlayerDieNotify)
		ADD_HANDLERMAP(proto::SceneAreaExploreNotify_CmdId_CMD_ID,	&CG4GameProcess::OnSceneAreaExploreNotify)
		ADD_HANDLERMAP(proto::AvatarAbilityResetFinishNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarAbilityResetFinishNotify)
		ADD_HANDLERMAP(proto::TakeoffEquipRsp_CmdId_CMD_ID,	&CG4GameProcess::OnTakeoffEquipRsp)
		ADD_HANDLERMAP(proto::SceneEntityDrownRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSceneEntityDrownRsp)
		ADD_HANDLERMAP(proto::SetPlayerHeadImageRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSetPlayerHeadImageRsp)
		ADD_HANDLERMAP(proto::BonusActivityUpdateNotify_CmdId_CMD_ID,	&CG4GameProcess::OnBonusActivityUpdateNotify)
		ADD_HANDLERMAP(proto::EvtAiSyncSkillCdNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEvtAiSyncSkillCdNotify)
		ADD_HANDLERMAP(proto::DungeonCandidateTeamDismissNotify_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonCandidateTeamDismissNotify)
		ADD_HANDLERMAP(proto::ActivityPlayOpenAnimNotify_CmdId_CMD_ID,	&CG4GameProcess::OnActivityPlayOpenAnimNotify)
		ADD_HANDLERMAP(proto::TakeCompoundOutputRsp_CmdId_CMD_ID,	&CG4GameProcess::OnTakeCompoundOutputRsp)
		ADD_HANDLERMAP(proto::GMShowNavMeshRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGMShowNavMeshRsp)
		ADD_HANDLERMAP(proto::EvtAvatarStandUpNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEvtAvatarStandUpNotify)
		ADD_HANDLERMAP(proto::GetInvestigationMonsterRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetInvestigationMonsterRsp)
		ADD_HANDLERMAP(proto::PlayerStoreNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerStoreNotify)
		ADD_HANDLERMAP(proto::GetPlayerTokenRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetPlayerTokenRsp)
		ADD_HANDLERMAP(proto::DungeonEntryToBeExploreNotify_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonEntryToBeExploreNotify)
		ADD_HANDLERMAP(proto::BattlePassAllDataNotify_CmdId_CMD_ID,	&CG4GameProcess::OnBattlePassAllDataNotify)
		ADD_HANDLERMAP(proto::EvtRushMoveNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEvtRushMoveNotify)
		ADD_HANDLERMAP(proto::EnterScenePeerNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEnterScenePeerNotify)
		ADD_HANDLERMAP(proto::MaterialDeleteUpdateNotify_CmdId_CMD_ID,	&CG4GameProcess::OnMaterialDeleteUpdateNotify)
		ADD_HANDLERMAP(proto::EntityFightPropNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEntityFightPropNotify)
		ADD_HANDLERMAP(proto::TakeBattlePassRewardRsp_CmdId_CMD_ID,	&CG4GameProcess::OnTakeBattlePassRewardRsp)
		ADD_HANDLERMAP(proto::AvatarExpeditionDataNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarExpeditionDataNotify)
		ADD_HANDLERMAP(proto::PlayerCookRsp_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerCookRsp)
		ADD_HANDLERMAP(proto::WatcherEventTypeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnWatcherEventTypeNotify)
		ADD_HANDLERMAP(proto::DungeonCandidateTeamInviteRsp_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonCandidateTeamInviteRsp)
		ADD_HANDLERMAP(proto::EvtEntityRenderersChangedNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEvtEntityRenderersChangedNotify)
		ADD_HANDLERMAP(proto::WorktopOptionNotify_CmdId_CMD_ID,	&CG4GameProcess::OnWorktopOptionNotify)
		ADD_HANDLERMAP(proto::GetSignInRewardRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetSignInRewardRsp)
		ADD_HANDLERMAP(proto::AvatarFetterDataNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarFetterDataNotify)
		ADD_HANDLERMAP(proto::SetSceneWeatherAreaRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSetSceneWeatherAreaRsp)
		ADD_HANDLERMAP(proto::ChangeAvatarRsp_CmdId_CMD_ID,	&CG4GameProcess::OnChangeAvatarRsp)
		ADD_HANDLERMAP(proto::AddQuestContentProgressRsp_CmdId_CMD_ID,	&CG4GameProcess::OnAddQuestContentProgressRsp)
		ADD_HANDLERMAP(proto::LeaveSceneRsp_CmdId_CMD_ID,	&CG4GameProcess::OnLeaveSceneRsp)
		ADD_HANDLERMAP(proto::ScenePointUnlockNotify_CmdId_CMD_ID,	&CG4GameProcess::OnScenePointUnlockNotify)
		ADD_HANDLERMAP(proto::WorldOwnerDailyTaskNotify_CmdId_CMD_ID,	&CG4GameProcess::OnWorldOwnerDailyTaskNotify)
		ADD_HANDLERMAP(proto::SceneEntityAppearNotify_CmdId_CMD_ID,	&CG4GameProcess::OnSceneEntityAppearNotify)
		ADD_HANDLERMAP(proto::WeaponAwakenRsp_CmdId_CMD_ID,	&CG4GameProcess::OnWeaponAwakenRsp)
		ADD_HANDLERMAP(proto::AvatarTeamUpdateNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarTeamUpdateNotify)
		ADD_HANDLERMAP(proto::DungeonCandidateTeamCreateRsp_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonCandidateTeamCreateRsp)
		ADD_HANDLERMAP(proto::WeaponPromoteRsp_CmdId_CMD_ID,	&CG4GameProcess::OnWeaponPromoteRsp)
		ADD_HANDLERMAP(proto::SceneKickPlayerRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSceneKickPlayerRsp)
		ADD_HANDLERMAP(proto::DestroyMassiveEntityNotify_CmdId_CMD_ID,	&CG4GameProcess::OnDestroyMassiveEntityNotify)
		ADD_HANDLERMAP(proto::PostEnterSceneRsp_CmdId_CMD_ID,	&CG4GameProcess::OnPostEnterSceneRsp)
		ADD_HANDLERMAP(proto::GetShopmallDataRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetShopmallDataRsp)
		ADD_HANDLERMAP(proto::EnterSceneReadyRsp_CmdId_CMD_ID,	&CG4GameProcess::OnEnterSceneReadyRsp)
		ADD_HANDLERMAP(proto::SceneTeamUpdateNotify_CmdId_CMD_ID,	&CG4GameProcess::OnSceneTeamUpdateNotify)
		ADD_HANDLERMAP(proto::CookGradeDataNotify_CmdId_CMD_ID,	&CG4GameProcess::OnCookGradeDataNotify)
		ADD_HANDLERMAP(proto::RefreshBackgroundAvatarRsp_CmdId_CMD_ID,	&CG4GameProcess::OnRefreshBackgroundAvatarRsp)
		ADD_HANDLERMAP(proto::ScenePlayerSoundNotify_CmdId_CMD_ID,	&CG4GameProcess::OnScenePlayerSoundNotify)
		ADD_HANDLERMAP(proto::EvtBulletDeactiveNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEvtBulletDeactiveNotify)
		ADD_HANDLERMAP(proto::DungeonWayPointActivateRsp_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonWayPointActivateRsp)
		ADD_HANDLERMAP(proto::EnterTransPointRegionNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEnterTransPointRegionNotify)
		ADD_HANDLERMAP(proto::PlayerCookArgsRsp_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerCookArgsRsp)
		ADD_HANDLERMAP(proto::BlossomChestInfoNotify_CmdId_CMD_ID,	&CG4GameProcess::OnBlossomChestInfoNotify)
		ADD_HANDLERMAP(proto::PlayerApplyEnterMpResultRsp_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerApplyEnterMpResultRsp)
		ADD_HANDLERMAP(proto::BattlePassCurScheduleUpdateNotify_CmdId_CMD_ID,	&CG4GameProcess::OnBattlePassCurScheduleUpdateNotify)
		ADD_HANDLERMAP(proto::ClientNewMailNotify_CmdId_CMD_ID,	&CG4GameProcess::OnClientNewMailNotify)
		ADD_HANDLERMAP(proto::EvtEntityStartDieEndNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEvtEntityStartDieEndNotify)
		ADD_HANDLERMAP(proto::QuestDelNotify_CmdId_CMD_ID,	&CG4GameProcess::OnQuestDelNotify)
		ADD_HANDLERMAP(proto::ItemCdGroupTimeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnItemCdGroupTimeNotify)
		ADD_HANDLERMAP(proto::BattlePassMissionUpdateNotify_CmdId_CMD_ID,	&CG4GameProcess::OnBattlePassMissionUpdateNotify)
		ADD_HANDLERMAP(proto::PlayerLoginRsp_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerLoginRsp)
		ADD_HANDLERMAP(proto::CreateMassiveEntityNotify_CmdId_CMD_ID,	&CG4GameProcess::OnCreateMassiveEntityNotify)
		ADD_HANDLERMAP(proto::CombineRsp_CmdId_CMD_ID,	&CG4GameProcess::OnCombineRsp)
		ADD_HANDLERMAP(proto::SealBattleBeginNotify_CmdId_CMD_ID,	&CG4GameProcess::OnSealBattleBeginNotify)
		ADD_HANDLERMAP(proto::AllSeenMonsterNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAllSeenMonsterNotify)
		ADD_HANDLERMAP(proto::WeaponUpgradeRsp_CmdId_CMD_ID,	&CG4GameProcess::OnWeaponUpgradeRsp)
		ADD_HANDLERMAP(proto::AnimatorForceSetAirMoveNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAnimatorForceSetAirMoveNotify)
		ADD_HANDLERMAP(proto::AvatarUnlockTalentNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarUnlockTalentNotify)
		ADD_HANDLERMAP(proto::SceneCreateEntityRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSceneCreateEntityRsp)
		ADD_HANDLERMAP(proto::WatcherEventNotify_CmdId_CMD_ID,	&CG4GameProcess::OnWatcherEventNotify)
		ADD_HANDLERMAP(proto::NpcTalkRsp_CmdId_CMD_ID,	&CG4GameProcess::OnNpcTalkRsp)
		ADD_HANDLERMAP(proto::AbilityInvocationsNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAbilityInvocationsNotify)
		ADD_HANDLERMAP(proto::PlatformRouteStateNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlatformRouteStateNotify)
		ADD_HANDLERMAP(proto::EntityFightPropUpdateNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEntityFightPropUpdateNotify)
		ADD_HANDLERMAP(proto::PlayerLuaShellNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerLuaShellNotify)
		ADD_HANDLERMAP(proto::QuestDestroyNpcRsp_CmdId_CMD_ID,	&CG4GameProcess::OnQuestDestroyNpcRsp)
		ADD_HANDLERMAP(proto::SceneRouteChangeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnSceneRouteChangeNotify)
		ADD_HANDLERMAP(proto::EntityMoveRoomNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEntityMoveRoomNotify)
		ADD_HANDLERMAP(proto::TowerLevelEndNotify_CmdId_CMD_ID,	&CG4GameProcess::OnTowerLevelEndNotify)
		ADD_HANDLERMAP(proto::PlayerEnterDungeonRsp_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerEnterDungeonRsp)
		ADD_HANDLERMAP(proto::SceneDestroyEntityRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSceneDestroyEntityRsp)
		ADD_HANDLERMAP(proto::LifeStateChangeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnLifeStateChangeNotify)
		ADD_HANDLERMAP(proto::RemoveRandTaskInfoNotify_CmdId_CMD_ID,	&CG4GameProcess::OnRemoveRandTaskInfoNotify)
		ADD_HANDLERMAP(proto::ActivityScheduleInfoNotify_CmdId_CMD_ID,	&CG4GameProcess::OnActivityScheduleInfoNotify)
		ADD_HANDLERMAP(proto::ServerBuffChangeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnServerBuffChangeNotify)
		ADD_HANDLERMAP(proto::ReadMailNotify_CmdId_CMD_ID,	&CG4GameProcess::OnReadMailNotify)
		ADD_HANDLERMAP(proto::WindSeedClientNotify_CmdId_CMD_ID,	&CG4GameProcess::OnWindSeedClientNotify)
		ADD_HANDLERMAP(proto::EvtDoSkillSuccNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEvtDoSkillSuccNotify)
		ADD_HANDLERMAP(proto::PlayerApplyEnterMpResultNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerApplyEnterMpResultNotify)
		ADD_HANDLERMAP(proto::PlayerChatCDNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerChatCDNotify)
		ADD_HANDLERMAP(proto::DungeonCandidateTeamInviteNotify_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonCandidateTeamInviteNotify)
		ADD_HANDLERMAP(proto::UnmarkEntityInMinMapNotify_CmdId_CMD_ID,	&CG4GameProcess::OnUnmarkEntityInMinMapNotify)
		ADD_HANDLERMAP(proto::CanUseSkillNotify_CmdId_CMD_ID,	&CG4GameProcess::OnCanUseSkillNotify)
		ADD_HANDLERMAP(proto::GetAuthkeyRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetAuthkeyRsp)
		ADD_HANDLERMAP(proto::ChangeTeamNameRsp_CmdId_CMD_ID,	&CG4GameProcess::OnChangeTeamNameRsp)
		ADD_HANDLERMAP(proto::DungeonCandidateTeamSetReadyRsp_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonCandidateTeamSetReadyRsp)
		ADD_HANDLERMAP(proto::ServerAnnounceNotify_CmdId_CMD_ID,	&CG4GameProcess::OnServerAnnounceNotify)
		ADD_HANDLERMAP(proto::AvatarExpeditionStartRsp_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarExpeditionStartRsp)
		ADD_HANDLERMAP(proto::TowerLevelStarCondNotify_CmdId_CMD_ID,	&CG4GameProcess::OnTowerLevelStarCondNotify)
		ADD_HANDLERMAP(proto::EvtAvatarEnterFocusNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEvtAvatarEnterFocusNotify)
		ADD_HANDLERMAP(proto::CutSceneEndNotify_CmdId_CMD_ID,	&CG4GameProcess::OnCutSceneEndNotify)
		ADD_HANDLERMAP(proto::DungeonFollowNotify_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonFollowNotify)
		ADD_HANDLERMAP(proto::PushTipsChangeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPushTipsChangeNotify)
		ADD_HANDLERMAP(proto::AvatarAddNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarAddNotify)
		ADD_HANDLERMAP(proto::WatcherChangeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnWatcherChangeNotify)
		ADD_HANDLERMAP(proto::AvatarSkillMaxChargeCountNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarSkillMaxChargeCountNotify)
		ADD_HANDLERMAP(proto::GetBlossomBriefInfoListRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetBlossomBriefInfoListRsp)
		ADD_HANDLERMAP(proto::GetActivityScheduleRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetActivityScheduleRsp)
		ADD_HANDLERMAP(proto::EvtBulletHitNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEvtBulletHitNotify)
		ADD_HANDLERMAP(proto::EvtAiSyncCombatThreatInfoNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEvtAiSyncCombatThreatInfoNotify)
		ADD_HANDLERMAP(proto::WorldOwnerBlossomBriefInfoNotify_CmdId_CMD_ID,	&CG4GameProcess::OnWorldOwnerBlossomBriefInfoNotify)
		ADD_HANDLERMAP(proto::PushTipsReadFinishRsp_CmdId_CMD_ID,	&CG4GameProcess::OnPushTipsReadFinishRsp)
		ADD_HANDLERMAP(proto::OrderFinishNotify_CmdId_CMD_ID,	&CG4GameProcess::OnOrderFinishNotify)
		ADD_HANDLERMAP(proto::CombatInvocationsNotify_CmdId_CMD_ID,	&CG4GameProcess::OnCombatInvocationsNotify)
		ADD_HANDLERMAP(proto::OpenStateUpdateNotify_CmdId_CMD_ID,	&CG4GameProcess::OnOpenStateUpdateNotify)
		ADD_HANDLERMAP(proto::WorldPlayerDieNotify_CmdId_CMD_ID,	&CG4GameProcess::OnWorldPlayerDieNotify)
		ADD_HANDLERMAP(proto::DealAddFriendRsp_CmdId_CMD_ID,	&CG4GameProcess::OnDealAddFriendRsp)
		ADD_HANDLERMAP(proto::AvatarEnterElementViewNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarEnterElementViewNotify)
		ADD_HANDLERMAP(proto::AvatarSkillChangeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarSkillChangeNotify)
		ADD_HANDLERMAP(proto::EntityPropNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEntityPropNotify)
		ADD_HANDLERMAP(proto::DungeonPlayerDieRsp_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonPlayerDieRsp)
		ADD_HANDLERMAP(proto::FocusAvatarRsp_CmdId_CMD_ID,	&CG4GameProcess::OnFocusAvatarRsp)
		ADD_HANDLERMAP(proto::DropItemRsp_CmdId_CMD_ID,	&CG4GameProcess::OnDropItemRsp)
		ADD_HANDLERMAP(proto::BuyShopmallGoodsRsp_CmdId_CMD_ID,	&CG4GameProcess::OnBuyShopmallGoodsRsp)
		ADD_HANDLERMAP(proto::AddSeenMonsterNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAddSeenMonsterNotify)
		ADD_HANDLERMAP(proto::AvatarFightPropNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarFightPropNotify)
		ADD_HANDLERMAP(proto::PlayerInvestigationAllInfoNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerInvestigationAllInfoNotify)
		ADD_HANDLERMAP(proto::TowerEnterLevelRsp_CmdId_CMD_ID,	&CG4GameProcess::OnTowerEnterLevelRsp)
		ADD_HANDLERMAP(proto::StoreWeightLimitNotify_CmdId_CMD_ID,	&CG4GameProcess::OnStoreWeightLimitNotify)
		ADD_HANDLERMAP(proto::DailyTaskProgressNotify_CmdId_CMD_ID,	&CG4GameProcess::OnDailyTaskProgressNotify)
		ADD_HANDLERMAP(proto::AvatarAbilityResetNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarAbilityResetNotify)
		ADD_HANDLERMAP(proto::PlayerEnterSceneNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerEnterSceneNotify)
		ADD_HANDLERMAP(proto::PlayerInvestigationTargetNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerInvestigationTargetNotify)
		ADD_HANDLERMAP(proto::SelectWorktopOptionRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSelectWorktopOptionRsp)
		ADD_HANDLERMAP(proto::TakePlayerLevelRewardRsp_CmdId_CMD_ID,	&CG4GameProcess::OnTakePlayerLevelRewardRsp)
		ADD_HANDLERMAP(proto::MarkNewNotify_CmdId_CMD_ID,	&CG4GameProcess::OnMarkNewNotify)
		ADD_HANDLERMAP(proto::GetPlayerMpModeAvailabilityRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetPlayerMpModeAvailabilityRsp)
		ADD_HANDLERMAP(proto::ChallengeDataNotify_CmdId_CMD_ID,	&CG4GameProcess::OnChallengeDataNotify)
		ADD_HANDLERMAP(proto::DungeonShowReminderNotify_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonShowReminderNotify)
		ADD_HANDLERMAP(proto::SceneAvatarStaminaStepRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSceneAvatarStaminaStepRsp)
		ADD_HANDLERMAP(proto::ClientTriggerEventNotify_CmdId_CMD_ID,	&CG4GameProcess::OnClientTriggerEventNotify)
		ADD_HANDLERMAP(proto::GivingRecordNotify_CmdId_CMD_ID,	&CG4GameProcess::OnGivingRecordNotify)
		ADD_HANDLERMAP(proto::ProudSkillChangeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnProudSkillChangeNotify)
		ADD_HANDLERMAP(proto::QuestUpdateQuestVarNotify_CmdId_CMD_ID,	&CG4GameProcess::OnQuestUpdateQuestVarNotify)
		ADD_HANDLERMAP(proto::GetGachaInfoRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetGachaInfoRsp)
		ADD_HANDLERMAP(proto::DungeonGetStatueDropRsp_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonGetStatueDropRsp)
		ADD_HANDLERMAP(proto::BattlePassMissionDelNotify_CmdId_CMD_ID,	&CG4GameProcess::OnBattlePassMissionDelNotify)
		ADD_HANDLERMAP(proto::HostPlayerNotify_CmdId_CMD_ID,	&CG4GameProcess::OnHostPlayerNotify)
		ADD_HANDLERMAP(proto::AvatarSkillInfoNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarSkillInfoNotify)
		ADD_HANDLERMAP(proto::PlayerCompoundMaterialRsp_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerCompoundMaterialRsp)
		ADD_HANDLERMAP(proto::WorldResinChangeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnWorldResinChangeNotify)
		ADD_HANDLERMAP(proto::ScenePlayerLocationNotify_CmdId_CMD_ID,	&CG4GameProcess::OnScenePlayerLocationNotify)
		ADD_HANDLERMAP(proto::AvatarDelNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarDelNotify)
		ADD_HANDLERMAP(proto::WorldDataNotify_CmdId_CMD_ID,	&CG4GameProcess::OnWorldDataNotify)
		ADD_HANDLERMAP(proto::RobotPushPlayerDataNotify_CmdId_CMD_ID,	&CG4GameProcess::OnRobotPushPlayerDataNotify)
		ADD_HANDLERMAP(proto::TowerCurLevelRecordChangeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnTowerCurLevelRecordChangeNotify)
		ADD_HANDLERMAP(proto::DungeonSlipRevivePointActivateRsp_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonSlipRevivePointActivateRsp)
		ADD_HANDLERMAP(proto::UnlockAvatarTalentRsp_CmdId_CMD_ID,	&CG4GameProcess::OnUnlockAvatarTalentRsp)
		ADD_HANDLERMAP(proto::AvatarUpgradeRsp_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarUpgradeRsp)
		ADD_HANDLERMAP(proto::QuestListNotify_CmdId_CMD_ID,	&CG4GameProcess::OnQuestListNotify)
		ADD_HANDLERMAP(proto::SceneAreaUnlockNotify_CmdId_CMD_ID,	&CG4GameProcess::OnSceneAreaUnlockNotify)
		ADD_HANDLERMAP(proto::GetAllMailRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetAllMailRsp)
		ADD_HANDLERMAP(proto::DropSubfieldRsp_CmdId_CMD_ID,	&CG4GameProcess::OnDropSubfieldRsp)
		ADD_HANDLERMAP(proto::BargainStartNotify_CmdId_CMD_ID,	&CG4GameProcess::OnBargainStartNotify)
		ADD_HANDLERMAP(proto::ForgeQueueManipulateRsp_CmdId_CMD_ID,	&CG4GameProcess::OnForgeQueueManipulateRsp)
		ADD_HANDLERMAP(proto::UseItemRsp_CmdId_CMD_ID,	&CG4GameProcess::OnUseItemRsp)
		ADD_HANDLERMAP(proto::ObstacleModifyNotify_CmdId_CMD_ID,	&CG4GameProcess::OnObstacleModifyNotify)
		ADD_HANDLERMAP(proto::ItemGivingRsp_CmdId_CMD_ID,	&CG4GameProcess::OnItemGivingRsp)
		ADD_HANDLERMAP(proto::MarkMapRsp_CmdId_CMD_ID,	&CG4GameProcess::OnMarkMapRsp)
		ADD_HANDLERMAP(proto::SceneTeamMPDisplayCurAvatarNotify_CmdId_CMD_ID,	&CG4GameProcess::OnSceneTeamMPDisplayCurAvatarNotify)
		ADD_HANDLERMAP(proto::DungeonChallengeBeginNotify_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonChallengeBeginNotify)
		ADD_HANDLERMAP(proto::PersonalSceneJumpRsp_CmdId_CMD_ID,	&CG4GameProcess::OnPersonalSceneJumpRsp)
		ADD_HANDLERMAP(proto::DungeonCandidateTeamInfoNotify_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonCandidateTeamInfoNotify)
		ADD_HANDLERMAP(proto::EndCameraSceneLookNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEndCameraSceneLookNotify)
		ADD_HANDLERMAP(proto::TriggerCreateGadgetToEquipPartNotify_CmdId_CMD_ID,	&CG4GameProcess::OnTriggerCreateGadgetToEquipPartNotify)
		ADD_HANDLERMAP(proto::AvatarExpeditionAllDataRsp_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarExpeditionAllDataRsp)
		ADD_HANDLERMAP(proto::SceneEntityMoveNotify_CmdId_CMD_ID,	&CG4GameProcess::OnSceneEntityMoveNotify)
		ADD_HANDLERMAP(proto::BonusActivityInfoRsp_CmdId_CMD_ID,	&CG4GameProcess::OnBonusActivityInfoRsp)
		ADD_HANDLERMAP(proto::WearEquipRsp_CmdId_CMD_ID,	&CG4GameProcess::OnWearEquipRsp)
		ADD_HANDLERMAP(proto::ExecuteGadgetLuaRsp_CmdId_CMD_ID,	&CG4GameProcess::OnExecuteGadgetLuaRsp)
		ADD_HANDLERMAP(proto::QuestListUpdateNotify_CmdId_CMD_ID,	&CG4GameProcess::OnQuestListUpdateNotify)
		ADD_HANDLERMAP(proto::AvatarExpeditionCallBackRsp_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarExpeditionCallBackRsp)
		ADD_HANDLERMAP(proto::SceneAreaWeatherNotify_CmdId_CMD_ID,	&CG4GameProcess::OnSceneAreaWeatherNotify)
		ADD_HANDLERMAP(proto::SetPlayerBornDataRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSetPlayerBornDataRsp)
		ADD_HANDLERMAP(proto::CookRecipeDataNotify_CmdId_CMD_ID,	&CG4GameProcess::OnCookRecipeDataNotify)
		ADD_HANDLERMAP(proto::AvatarSkillUpgradeRsp_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarSkillUpgradeRsp)
		ADD_HANDLERMAP(proto::PlayerApplyEnterMpNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerApplyEnterMpNotify)
		ADD_HANDLERMAP(proto::BonusActivityAllDataNotify_CmdId_CMD_ID,	&CG4GameProcess::OnBonusActivityAllDataNotify)
		ADD_HANDLERMAP(proto::PlayerGameTimeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerGameTimeNotify)
		ADD_HANDLERMAP(proto::EvtAvatarExitFocusNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEvtAvatarExitFocusNotify)
		ADD_HANDLERMAP(proto::EnterSceneDoneRsp_CmdId_CMD_ID,	&CG4GameProcess::OnEnterSceneDoneRsp)
		ADD_HANDLERMAP(proto::ClientTransmitRsp_CmdId_CMD_ID,	&CG4GameProcess::OnClientTransmitRsp)
		ADD_HANDLERMAP(proto::BigTalentPointConvertRsp_CmdId_CMD_ID,	&CG4GameProcess::OnBigTalentPointConvertRsp)
		ADD_HANDLERMAP(proto::SceneWeatherForcastRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSceneWeatherForcastRsp)
		ADD_HANDLERMAP(proto::TakeMaterialDeleteReturnRsp_CmdId_CMD_ID,	&CG4GameProcess::OnTakeMaterialDeleteReturnRsp)
		ADD_HANDLERMAP(proto::GetOnlinePlayerListRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetOnlinePlayerListRsp)
		ADD_HANDLERMAP(proto::SceneEntityMoveRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSceneEntityMoveRsp)
		ADD_HANDLERMAP(proto::LogCutsceneNotify_CmdId_CMD_ID,	&CG4GameProcess::OnLogCutsceneNotify)
		ADD_HANDLERMAP(proto::ServerAnnounceRevokeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnServerAnnounceRevokeNotify)
		ADD_HANDLERMAP(proto::DungeonEntryInfoRsp_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonEntryInfoRsp)
		ADD_HANDLERMAP(proto::EnterWorldAreaRsp_CmdId_CMD_ID,	&CG4GameProcess::OnEnterWorldAreaRsp)
		ADD_HANDLERMAP(proto::DelMailRsp_CmdId_CMD_ID,	&CG4GameProcess::OnDelMailRsp)
		ADD_HANDLERMAP(proto::AskAddFriendRsp_CmdId_CMD_ID,	&CG4GameProcess::OnAskAddFriendRsp)
		ADD_HANDLERMAP(proto::PlayerQuitFromMpNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerQuitFromMpNotify)
		ADD_HANDLERMAP(proto::GmTalkRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGmTalkRsp)
		ADD_HANDLERMAP(proto::SceneForceUnlockNotify_CmdId_CMD_ID,	&CG4GameProcess::OnSceneForceUnlockNotify)
		ADD_HANDLERMAP(proto::SeaLampContributeItemRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSeaLampContributeItemRsp)
		ADD_HANDLERMAP(proto::PlayerPreEnterMpNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerPreEnterMpNotify)
		ADD_HANDLERMAP(proto::SeeMonsterRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSeeMonsterRsp)
		ADD_HANDLERMAP(proto::ServerLogNotify_CmdId_CMD_ID,	&CG4GameProcess::OnServerLogNotify)
		ADD_HANDLERMAP(proto::AvatarPropNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarPropNotify)
		ADD_HANDLERMAP(proto::GetShopmallShopDataRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetShopmallShopDataRsp)
		ADD_HANDLERMAP(proto::SetPlayerPropRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSetPlayerPropRsp)
		ADD_HANDLERMAP(proto::DungeonCandidateTeamKickRsp_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonCandidateTeamKickRsp)
		ADD_HANDLERMAP(proto::MassiveEntityStateChangedNotify_CmdId_CMD_ID,	&CG4GameProcess::OnMassiveEntityStateChangedNotify)
		ADD_HANDLERMAP(proto::PlayerSetLanguageRsp_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerSetLanguageRsp)
		ADD_HANDLERMAP(proto::FinishedParentQuestUpdateNotify_CmdId_CMD_ID,	&CG4GameProcess::OnFinishedParentQuestUpdateNotify)
		ADD_HANDLERMAP(proto::TowerGetFloorStarRewardRsp_CmdId_CMD_ID,	&CG4GameProcess::OnTowerGetFloorStarRewardRsp)
		ADD_HANDLERMAP(proto::DungeonSettleNotify_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonSettleNotify)
		ADD_HANDLERMAP(proto::EntityAuthorityChangeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEntityAuthorityChangeNotify)
		ADD_HANDLERMAP(proto::SignInAllDataNotify_CmdId_CMD_ID,	&CG4GameProcess::OnSignInAllDataNotify)
		ADD_HANDLERMAP(proto::PlayerPropChangeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerPropChangeNotify)
		ADD_HANDLERMAP(proto::PingRsp_CmdId_CMD_ID,	&CG4GameProcess::OnPingRsp)
		ADD_HANDLERMAP(proto::StoreItemDelNotify_CmdId_CMD_ID,	&CG4GameProcess::OnStoreItemDelNotify)
		ADD_HANDLERMAP(proto::TakeBattlePassMissionPointRsp_CmdId_CMD_ID,	&CG4GameProcess::OnTakeBattlePassMissionPointRsp)
		ADD_HANDLERMAP(proto::EntityForceSyncRsp_CmdId_CMD_ID,	&CG4GameProcess::OnEntityForceSyncRsp)
		ADD_HANDLERMAP(proto::GetScenePointRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetScenePointRsp)
		ADD_HANDLERMAP(proto::ElementReactionLogNotify_CmdId_CMD_ID,	&CG4GameProcess::OnElementReactionLogNotify)
		ADD_HANDLERMAP(proto::SeaLampTakePhaseRewardRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSeaLampTakePhaseRewardRsp)
		ADD_HANDLERMAP(proto::GadgetInteractRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGadgetInteractRsp)
		ADD_HANDLERMAP(proto::ServerDisconnectClientNotify_CmdId_CMD_ID,	&CG4GameProcess::OnServerDisconnectClientNotify)
		ADD_HANDLERMAP(proto::SceneTimeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnSceneTimeNotify)
		ADD_HANDLERMAP(proto::ScenePlayerInfoNotify_CmdId_CMD_ID,	&CG4GameProcess::OnScenePlayerInfoNotify)
		ADD_HANDLERMAP(proto::KeepAliveNotify_CmdId_CMD_ID,	&CG4GameProcess::OnKeepAliveNotify)
		ADD_HANDLERMAP(proto::EvtBeingHitsCombineNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEvtBeingHitsCombineNotify)
		ADD_HANDLERMAP(proto::ClientAbilityInitFinishNotify_CmdId_CMD_ID,	&CG4GameProcess::OnClientAbilityInitFinishNotify)
		ADD_HANDLERMAP(proto::AvatarBuffAddNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarBuffAddNotify)
		ADD_HANDLERMAP(proto::DungeonDataNotify_CmdId_CMD_ID,	&CG4GameProcess::OnDungeonDataNotify)
		ADD_HANDLERMAP(proto::ExitTransPointRegionNotify_CmdId_CMD_ID,	&CG4GameProcess::OnExitTransPointRegionNotify)
		ADD_HANDLERMAP(proto::AvatarPromoteRsp_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarPromoteRsp)
		ADD_HANDLERMAP(proto::ClientFpsStatusNotify_CmdId_CMD_ID,	&CG4GameProcess::OnClientFpsStatusNotify)
		ADD_HANDLERMAP(proto::PlayerChatRsp_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerChatRsp)
		ADD_HANDLERMAP(proto::QuestUpdateQuestVarRsp_CmdId_CMD_ID,	&CG4GameProcess::OnQuestUpdateQuestVarRsp)
		ADD_HANDLERMAP(proto::TowerTeamSelectRsp_CmdId_CMD_ID,	&CG4GameProcess::OnTowerTeamSelectRsp)
		ADD_HANDLERMAP(proto::MonsterSummonTagNotify_CmdId_CMD_ID,	&CG4GameProcess::OnMonsterSummonTagNotify)
		ADD_HANDLERMAP(proto::ActivityInfoNotify_CmdId_CMD_ID,	&CG4GameProcess::OnActivityInfoNotify)
		ADD_HANDLERMAP(proto::SetPlayerBirthdayRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSetPlayerBirthdayRsp)
		ADD_HANDLERMAP(proto::EvtCostStaminaNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEvtCostStaminaNotify)
		ADD_HANDLERMAP(proto::ChatHistoryNotify_CmdId_CMD_ID,	&CG4GameProcess::OnChatHistoryNotify)
		ADD_HANDLERMAP(proto::QueryPathRsp_CmdId_CMD_ID,	&CG4GameProcess::OnQueryPathRsp)
		ADD_HANDLERMAP(proto::PlayerLogoutRsp_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerLogoutRsp)
		ADD_HANDLERMAP(proto::SealBattleEndNotify_CmdId_CMD_ID,	&CG4GameProcess::OnSealBattleEndNotify)
		ADD_HANDLERMAP(proto::ChangeGameTimeRsp_CmdId_CMD_ID,	&CG4GameProcess::OnChangeGameTimeRsp)
		ADD_HANDLERMAP(proto::TowerBriefDataNotify_CmdId_CMD_ID,	&CG4GameProcess::OnTowerBriefDataNotify)
		ADD_HANDLERMAP(proto::ProudSkillExtraLevelNotify_CmdId_CMD_ID,	&CG4GameProcess::OnProudSkillExtraLevelNotify)
		ADD_HANDLERMAP(proto::PlayerEnterSceneInfoNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerEnterSceneInfoNotify)
		ADD_HANDLERMAP(proto::AbilityInvocationFixedNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAbilityInvocationFixedNotify)
		ADD_HANDLERMAP(proto::ClientReconnectNotify_CmdId_CMD_ID,	&CG4GameProcess::OnClientReconnectNotify)
		ADD_HANDLERMAP(proto::AvatarSkillDepotChangeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarSkillDepotChangeNotify)
		ADD_HANDLERMAP(proto::GetSceneAreaRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetSceneAreaRsp)
		ADD_HANDLERMAP(proto::EvtAnimatorParameterNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEvtAnimatorParameterNotify)
		ADD_HANDLERMAP(proto::LoadActivityTerrainNotify_CmdId_CMD_ID,	&CG4GameProcess::OnLoadActivityTerrainNotify)
		ADD_HANDLERMAP(proto::ReliquaryUpgradeRsp_CmdId_CMD_ID,	&CG4GameProcess::OnReliquaryUpgradeRsp)
		ADD_HANDLERMAP(proto::DeleteFriendRsp_CmdId_CMD_ID,	&CG4GameProcess::OnDeleteFriendRsp)
		ADD_HANDLERMAP(proto::ProudSkillUpgradeRsp_CmdId_CMD_ID,	&CG4GameProcess::OnProudSkillUpgradeRsp)
		ADD_HANDLERMAP(proto::SceneInitFinishRsp_CmdId_CMD_ID,	&CG4GameProcess::OnSceneInitFinishRsp)
		ADD_HANDLERMAP(proto::GadgetStateNotify_CmdId_CMD_ID,	&CG4GameProcess::OnGadgetStateNotify)
		ADD_HANDLERMAP(proto::LockWorldFogAreaNotify_CmdId_CMD_ID,	&CG4GameProcess::OnLockWorldFogAreaNotify)
		ADD_HANDLERMAP(proto::EvtFaceToDirNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEvtFaceToDirNotify)
		ADD_HANDLERMAP(proto::GetQuestTalkHistoryRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetQuestTalkHistoryRsp)
		ADD_HANDLERMAP(proto::AvatarCardChangeRsp_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarCardChangeRsp)
		ADD_HANDLERMAP(proto::PlatformStartRouteNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlatformStartRouteNotify)
		ADD_HANDLERMAP(proto::BlossomBriefInfoNotify_CmdId_CMD_ID,	&CG4GameProcess::OnBlossomBriefInfoNotify)
		ADD_HANDLERMAP(proto::GetShopRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetShopRsp)
		ADD_HANDLERMAP(proto::DailyTaskScoreRewardNotify_CmdId_CMD_ID,	&CG4GameProcess::OnDailyTaskScoreRewardNotify)
		ADD_HANDLERMAP(proto::GetDailyDungeonEntryInfoRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetDailyDungeonEntryInfoRsp)
		ADD_HANDLERMAP(proto::AvatarChangeElementTypeRsp_CmdId_CMD_ID,	&CG4GameProcess::OnAvatarChangeElementTypeRsp)
		ADD_HANDLERMAP(proto::GetSceneNpcPositionRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetSceneNpcPositionRsp)
		ADD_HANDLERMAP(proto::PlayerRandomCookRsp_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerRandomCookRsp)
		ADD_HANDLERMAP(proto::ForgeGetQueueDataRsp_CmdId_CMD_ID,	&CG4GameProcess::OnForgeGetQueueDataRsp)
		ADD_HANDLERMAP(proto::MailChangeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnMailChangeNotify)
		ADD_HANDLERMAP(proto::EvtFaceToEntityNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEvtFaceToEntityNotify)
		ADD_HANDLERMAP(proto::ChapterStateNotify_CmdId_CMD_ID,	&CG4GameProcess::OnChapterStateNotify)
		ADD_HANDLERMAP(proto::WorldPlayerReviveRsp_CmdId_CMD_ID,	&CG4GameProcess::OnWorldPlayerReviveRsp)
		ADD_HANDLERMAP(proto::BossChestActivateNotify_CmdId_CMD_ID,	&CG4GameProcess::OnBossChestActivateNotify)
		ADD_HANDLERMAP(proto::JoinPlayerSceneRsp_CmdId_CMD_ID,	&CG4GameProcess::OnJoinPlayerSceneRsp)
		ADD_HANDLERMAP(proto::EvtAvatarUpdateFocusNotify_CmdId_CMD_ID,	&CG4GameProcess::OnEvtAvatarUpdateFocusNotify)
		ADD_HANDLERMAP(proto::ClientReportNotify_CmdId_CMD_ID,	&CG4GameProcess::OnClientReportNotify)
		ADD_HANDLERMAP(proto::PlayerTimeNotify_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerTimeNotify)
		ADD_HANDLERMAP(proto::AbilityInvocationFailNotify_CmdId_CMD_ID,	&CG4GameProcess::OnAbilityInvocationFailNotify)
		ADD_HANDLERMAP(proto::DataResVersionNotify_CmdId_CMD_ID,	&CG4GameProcess::OnDataResVersionNotify)
		ADD_HANDLERMAP(proto::PlayerSetPauseRsp_CmdId_CMD_ID,	&CG4GameProcess::OnPlayerSetPauseRsp)
		ADD_HANDLERMAP(proto::DelTeamEntityNotify_CmdId_CMD_ID,	&CG4GameProcess::OnDelTeamEntityNotify)
		ADD_HANDLERMAP(proto::GetActivityInfoRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetActivityInfoRsp)
		ADD_HANDLERMAP(proto::GetBonusActivityRewardRsp_CmdId_CMD_ID,	&CG4GameProcess::OnGetBonusActivityRewardRsp)
		ADD_HANDLERMAP(proto::DropHintNotify_CmdId_CMD_ID,	&CG4GameProcess::OnDropHintNotify)
		ADD_HANDLERMAP(proto::CompoundDataNotify_CmdId_CMD_ID,	&CG4GameProcess::OnCompoundDataNotify)
		//auto created code end
	REGISTERHANDLER_END()

private:
	//解包时使用的临时变量
	Packet m_packet;
};
#endif


