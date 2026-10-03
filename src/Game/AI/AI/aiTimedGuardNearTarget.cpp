#include "Game/AI/AI/aiTimedGuardNearTarget.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71005E0AAC.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

TimedGuardNearTarget::TimedGuardNearTarget(const InitArg& arg) : GuardNearTarget(arg) {}

TimedGuardNearTarget::~TimedGuardNearTarget() = default;

bool TimedGuardNearTarget::init_(sead::Heap* heap) {
    return GuardNearTarget::init_(heap);
}

void TimedGuardNearTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    const int time = *mGuardEndTime_s;
    _a4 = time;
    _a8 = time;
    _a0 = time;
    GuardNearTarget::enter_(params);
}

void TimedGuardNearTarget::calc_() {
    f32& timer = _a0;
    if (m39(sub_710044C9E8())) {
        ksys::Timer::update(&timer, -1.0f);
    } else {
        s32 time = _a4;
        if (_a8 != _a4)
            time = sead::GlobalRandom::instance()->getS32Range(_a4, _a8);
        timer = time;
    }
    GuardNearTarget::calc_();
}

void TimedGuardNearTarget::leave_() {
    GuardNearTarget::leave_();
}

void TimedGuardNearTarget::loadParams_() {
    GuardNearTarget::loadParams_();
    getStaticParam(&mGuardEndTime_s, "GuardEndTime");
    getStaticParam(&mGuardStartAngle_s, "GuardStartAngle");
    getStaticParam(&mGuardEndAngle_s, "GuardEndAngle");
}

bool TimedGuardNearTarget::m35() {
    bool result = false;
    auto* target = sub_71005D9050(mActor);
    if (target && ksys::act::isPlayerProfile(target) &&
        sub_71005E0AAC(mActor, false, *mGuardStartAngle_s)) {
        ksys::act::acc::PlayerBase player;
        ksys::act::acquireActor(&ksys::act::PlayerInfo::getSomeProcLink(), &player);
        result = player.m302();
    }
    return result;
}

bool TimedGuardNearTarget::m39(float distance) {
    auto* target = sub_71005D9050(mActor);
    const bool not_player = !target || !ksys::act::isPlayerProfile(target);
    const bool guarding = GuardNearTarget::m36(distance);
    bool result = not_player && guarding;
    if (!not_player && guarding)
        result = !sub_71005E0AAC(mActor, true, *mGuardEndAngle_s);
    return result;
}

bool TimedGuardNearTarget::m36(float distance) {
    return _a0 <= 0.0f;
}

}  // namespace uking::ai
