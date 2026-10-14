#include "Game/Actor/AI/aiInvincibleNearTarget.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71005E0AAC.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

InvincibleNearTarget::InvincibleNearTarget(const InitArg& arg) : InvincibleNearTargetBase(arg) {}

InvincibleNearTarget::~InvincibleNearTarget() = default;

bool InvincibleNearTarget::init_(sead::Heap* heap) {
    return InvincibleNearTargetBase::init_(heap);
}

void InvincibleNearTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    const int time = *mGuardEndTime_s;
    _a4 = time;
    _a8 = time;
    _a0 = time;
    InvincibleNearTargetBase::enter_(params);
}

void InvincibleNearTarget::calc_() {
    f32& timer = _a0;
    if (m39(sub_710044C9E8())) {
        ksys::Timer::update(&timer, -1.0f);
    } else {
        s32 time = _a4;
        if (_a8 != _a4)
            time = sead::GlobalRandom::instance()->getS32Range(_a4, _a8);
        timer = time;
    }
    InvincibleNearTargetBase::calc_();
}

void InvincibleNearTarget::leave_() {
    InvincibleNearTargetBase::leave_();
}

void InvincibleNearTarget::loadParams_() {
    InvincibleNearTargetBase::loadParams_();
    getStaticParam(&mGuardEndTime_s, "GuardEndTime");
    getStaticParam(&mGuardStartAngle_s, "GuardStartAngle");
    getStaticParam(&mGuardEndAngle_s, "GuardEndAngle");
}

bool InvincibleNearTarget::m35(float distance) {
    bool result = false;
    auto* target = sub_71005D9050(mActor);
    if (target && ksys::act::isPlayerProfile(target) &&
        sub_71005E0AAC(mActor, false, *mGuardStartAngle_s)) {
        ksys::act::acc::PlayerBase player;
        ksys::act::acquireActor(&uking::act::PlayerInfo::getSomeProcLink(), &player);
        result = player.m302();
    }
    return result;
}

bool InvincibleNearTarget::m39(float distance) {
    auto* target = sub_71005D9050(mActor);
    const bool not_player = !target || !ksys::act::isPlayerProfile(target);
    const bool guarding = InvincibleNearTargetBase::m36(distance);
    bool result = not_player && guarding;
    if (!not_player && guarding)
        result = !sub_71005E0AAC(mActor, true, *mGuardEndAngle_s);
    return result;
}

bool InvincibleNearTarget::m36(float distance) {
    return _a0 <= 0.0f;
}

}  // namespace uking::ai
