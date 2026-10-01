#include "Game/AI/AI/aiWolfLinkNormalRoot.h"
#include "Game/Actor/actWolfLink.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWolfLink.h"

namespace uking::ai {

// NON_MATCHING: store pairing/scheduling (_140's MesTransceiverId, _198/_1a8/_1b0)
WolfLinkNormalRoot::WolfLinkNormalRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkNormalRoot::~WolfLinkNormalRoot() = default;

bool WolfLinkNormalRoot::init_(sead::Heap* heap) {
    _1b8 = 0;
    _70 = sead::DynamicCast<act::WolfLink>(mActor);
    if (!_70)
        return false;

    const auto* param = _70->getParam();
    if (!param)
        return false;
    const auto* gparams = param->getRes().mGParamList;
    if (!gparams)
        return false;
    _78 = gparams->getWolfLink();
    if (!_78)
        return false;

    _80 = mActor->getAwareness();
    return _80 != nullptr;
}

void WolfLinkNormalRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WolfLinkNormalRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WolfLinkNormalRoot::loadParams_() {
    getStaticParam(&mShiekSensorLeadDistance_s, "ShiekSensorLeadDistance");
    getStaticParam(&mShiekSensorGoalTolerance_s, "ShiekSensorGoalTolerance");
    getStaticParam(&mShiekSensorTargetFowardOffset_s, "ShiekSensorTargetFowardOffset");
    getStaticParam(&mBattleAggressionRange_s, "BattleAggressionRange");
    getStaticParam(&mHowlAtEnemyRange_s, "HowlAtEnemyRange");
    getStaticParam(&mUtilityWantsToHunt_s, "UtilityWantsToHunt");
    getStaticParam(&mWarpToPlayerDistance_s, "WarpToPlayerDistance");
}

}  // namespace uking::ai
