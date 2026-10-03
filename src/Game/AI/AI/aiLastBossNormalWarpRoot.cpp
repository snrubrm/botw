#include "Game/AI/AI/aiLastBossNormalWarpRoot.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LastBossNormalWarpRoot::LastBossNormalWarpRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
LastBossNormalWarpRoot::~LastBossNormalWarpRoot() {
    ;
}

bool LastBossNormalWarpRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LastBossNormalWarpRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool LastBossNormalWarpRoot::isChangeable() const {
    return false;
}

void LastBossNormalWarpRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LastBossNormalWarpRoot::loadParams_() {
    getStaticParam(&mIsKeepDisableDraw_s, "IsKeepDisableDraw");
    getStaticParam(&mSleepPartsActorName_s, "SleepPartsActorName");
    getDynamicParam(&mIsReturnHome_d, "IsReturnHome");
    getDynamicParam(&mIsForceWarp_d, "IsForceWarp");
    getDynamicParam(&mIsPartsActorTgOn_d, "IsPartsActorTgOn");
    getDynamicParam(&mIsPartsWarpEffectSync_d, "IsPartsWarpEffectSync");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void LastBossNormalWarpRoot::calc_() {
    auto* child = getCurrentChild();
    if (!child || (!child->isFinished() && !child->isFailed()))
        return;

    if (isCurrentChild("ワープ前行動")) {
        m36();
    } else if (isCurrentChild("ワープ")) {
        m37();
    } else if (isCurrentChild("ワープ後行動")) {
        if (child->isFinished() && !*mIsReturnHome_d)
            setFinished();
        else
            setFailed();
    }
}

void LastBossNormalWarpRoot::m34() {
    ksys::act::ai::InlineParamPack pack;
    pack.addBool(*mIsPartsWarpEffectSync_d, "IsPartsWarpEffectSync", -1);
    changeChild("ワープ前行動", &pack);
}

void LastBossNormalWarpRoot::m35(ksys::act::ai::InlineParamPack* params) {
    params->addBool(*mIsReturnHome_d, "IsReturnHome", -1);
    params->addBool(*mIsForceWarp_d, "IsForceWarp", -1);
}

void LastBossNormalWarpRoot::m36() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addBool(*mIsPartsActorTgOn_d, "IsPartsActorTgOn", -1);
    pack.addBool(*mIsReturnHome_d && *mIsKeepDisableDraw_s, "IsKeepDisableDraw", -1);
    m35(&pack);
    changeChild("ワープ", &pack);
}

void LastBossNormalWarpRoot::m37() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addBool(*mIsReturnHome_d && *mIsKeepDisableDraw_s, "IsKeepDisableDraw", -1);
    pack.addBool(*mIsPartsActorTgOn_d, "IsPartsActorTgOn", -1);
    pack.addBool(*mIsPartsWarpEffectSync_d, "IsPartsWarpEffectSync", -1);
    changeChild("ワープ後行動", &pack);
}

}  // namespace uking::ai
