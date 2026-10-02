#include "Game/AI/Action/actionHorseRideChargeCommand.h"
#include <prim/seadScopedLock.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseRideChargeCommand::HorseRideChargeCommand(const InitArg& arg) : HorseRideMoveCommand(arg) {}

// NON_MATCHING: instruction scheduling (the original computes &payload lock before the sender vtable stores)
HorseRideChargeCommand::~HorseRideChargeCommand() = default;

bool HorseRideChargeCommand::init_(sead::Heap* heap) {
    return HorseRideMoveCommand::init_(heap);
}

void HorseRideChargeCommand::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideMoveCommand::enter_(params);
}

void HorseRideChargeCommand::leave_() {
    HorseRideMoveCommand::leave_();
}

void HorseRideChargeCommand::loadParams_() {
    HorseRideMoveCommand::loadParams_();
}

void HorseRideChargeCommand::calc_() {
    HorseRideMoveCommand::calc_();
}

bool HorseRideChargeCommand::m32(ksys::act::Actor* actor) {
    auto* target = sub_71005D9050(mActor);
    if (!target)
        return false;
    {
        sead::ScopedLock<sead::CriticalSection> lock(&_98.mLock);
        _98._58 = *target;
        _98._68 = 0;
    }
    if (!_98.sub_710070DC38(actor, true))
        return false;
    return HorseRideMoveCommand::m32(actor);
}

}  // namespace uking::action
