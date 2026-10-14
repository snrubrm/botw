#include "Game/Actor/Action/actionHorseRideChaseCommand.h"
#include <prim/seadScopedLock.h>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseRideChaseCommand::HorseRideChaseCommand(const InitArg& arg) : HorseRideSetGearCommand(arg) {}

// NON_MATCHING: instruction scheduling (the original computes &payload lock before the sender vtable stores)
HorseRideChaseCommand::~HorseRideChaseCommand() = default;

bool HorseRideChaseCommand::init_(sead::Heap* heap) {
    return HorseRideSetGearCommand::init_(heap);
}

void HorseRideChaseCommand::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideSetGearCommand::enter_(params);
}

void HorseRideChaseCommand::leave_() {
    HorseRideSetGearCommand::leave_();
}

void HorseRideChaseCommand::loadParams_() {
    HorseRideSetGearCommand::loadParams_();
    getStaticParam(&mChaseKeepDist_s, "ChaseKeepDist");
}

void HorseRideChaseCommand::calc_() {
    HorseRideSetGearCommand::calc_();
}

bool HorseRideChaseCommand::m32(ksys::act::Actor* actor) {
    auto* target = sub_71005D9050(mActor);
    if (!target)
        return false;
    const f32 keep_dist = *mChaseKeepDist_s;
    {
        sead::ScopedLock<sead::CriticalSection> lock(&_a0.mLock);
        _a0._58 = *target;
        _a0._68 = keep_dist;
    }
    if (!_a0.sub_710070DC38(actor, true))
        return false;
    return HorseRideSetGearCommand::m32(actor);
}

}  // namespace uking::action
