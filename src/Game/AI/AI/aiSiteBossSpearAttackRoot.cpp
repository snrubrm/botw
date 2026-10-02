#include "Game/AI/AI/aiSiteBossSpearAttackRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actSiteBoss.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

SiteBossSpearAttackRoot::SiteBossSpearAttackRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossSpearAttackRoot::~SiteBossSpearAttackRoot() = default;

bool SiteBossSpearAttackRoot::init_(sead::Heap* heap) {
    if (auto* model = mActor->getModel())
        _f0.search(model, "Head");
    else
        _f0.getKey().reset();
    _da = false;
    _e4 = 0;
    _e8 = 0;
    return true;
}

void SiteBossSpearAttackRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossSpearAttackRoot::leave_() {
    auto* boss = sead::DynamicCast<act::SiteBoss>(mActor);
    if (boss && !boss->_1558.isOnBit(13))
        changeAS("ForceRepair", false, 0, 0);
}

void SiteBossSpearAttackRoot::loadParams_() {
    getStaticParam(&mThrowSpearRate_s, "ThrowSpearRate");
    getStaticParam(&mBeamRate_s, "BeamRate");
    getStaticParam(&mIceBulletRate_s, "IceBulletRate");
    getStaticParam(&mSweepRateAtFar_s, "SweepRateAtFar");
    getStaticParam(&mSweepRateAtNear_s, "SweepRateAtNear");
    getStaticParam(&mReturnWaitCount_s, "ReturnWaitCount");
    getStaticParam(&mBeamPatternChangeHP_s, "BeamPatternChangeHP");
    getStaticParam(&mFarDistanceAttackRange_s, "FarDistanceAttackRange");
    getStaticParam(&mNearDistanceAttackRange_s, "NearDistanceAttackRange");
    getStaticParam(&mVerticalAttackRange_s, "VerticalAttackRange");
    getStaticParam(&mOnIceBlockHeight_s, "OnIceBlockHeight");
    getStaticParam(&mIsBowAimedCounterOn_s, "IsBowAimedCounterOn");
    getStaticParam(&mIsIceBulletOn_s, "IsIceBulletOn");
    getStaticParam(&mWarpAnchorFirstSuffix_s, "WarpAnchorFirstSuffix");
    getStaticParam(&mWarpAnchorAfterSuffix_s, "WarpAnchorAfterSuffix");
    getStaticParam(&mChaseDist_s, "ChaseDist");
    getStaticParam(&mChaseDistOffset_s, "ChaseDistOffset");
    getDynamicParam(&mIsAttackPatternFixed_d, "IsAttackPatternFixed");
}

void SiteBossSpearAttackRoot::m34(sead::Vector3f* pos) {
    auto* actor = mActor;
    if (!actor)
        return;

    auto* link = sub_71005D9050(actor);
    if (link && link->hasProc() && ksys::act::isPlayerProfile(link))
        *pos = sub_71005D9330(actor);
    else
        *pos = getPlayerPosition();
}

}  // namespace uking::ai
