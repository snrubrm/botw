#include "Game/AI/AI/aiSiteBossRecognizeRootBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actLastBoss.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

SiteBossRecognizeRootBase::SiteBossRecognizeRootBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossRecognizeRootBase::~SiteBossRecognizeRootBase() = default;

bool SiteBossRecognizeRootBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original computes the getU32 argument before loading the GlobalRandom instance
// (C++14 evaluation order)
void SiteBossRecognizeRootBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (!actor)
        return;

    _64 = 0;
    if (mAttackNum_s)
        _60 = *mAttackNum_s + sead::GlobalRandom::instance()->getU32(*mAttackRandNum_s + 1);
    else
        _60 = 1;

    if (!actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_2000000))
        sub_7100478B7C();
    else if (m35())
        m40();
    else
        siteBossStuff();

    actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
}

void SiteBossRecognizeRootBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossRecognizeRootBase::loadParams_() {
    getStaticParam(&mAttackNum_s, "AttackNum");
    getStaticParam(&mAttackRandNum_s, "AttackRandNum");
    getStaticParam(&mWarpStartDist_s, "WarpStartDist");
    getStaticParam(&mForceWarpRetryDist_s, "ForceWarpRetryDist");
    getDynamicParam(&mIsAttackPatternFixed_d, "IsAttackPatternFixed");
}

void SiteBossRecognizeRootBase::m34(bool on) {}

bool SiteBossRecognizeRootBase::m36() {
    if (*mAttackNum_s == 0)
        return false;
    return _64 >= _60;
}

void SiteBossRecognizeRootBase::m37() {
    // The original performs the cast and discards the result.
    sead::DynamicCast<act::LastBoss>(mActor);
    m34(false);
}

void SiteBossRecognizeRootBase::m38(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f pos;
    SiteBossRecognizeRootBase::m39(&pos);
    params->addVec3(pos, "TargetPos", -1);
    params->addBool(*mIsAttackPatternFixed_d, "IsAttackPatternFixed", -1);
}

void SiteBossRecognizeRootBase::m39(sead::Vector3f* pos) {
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
