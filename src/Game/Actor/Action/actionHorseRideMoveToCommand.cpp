#include "Game/Actor/Action/actionHorseRideMoveToCommand.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseRideMoveToCommand::HorseRideMoveToCommand(const InitArg& arg) : HorseRideSetGearCommand(arg) {}

HorseRideMoveToCommand::~HorseRideMoveToCommand() = default;

bool HorseRideMoveToCommand::init_(sead::Heap* heap) {
    return HorseRideSetGearCommand::init_(heap);
}

void HorseRideMoveToCommand::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideSetGearCommand::enter_(params);
}

void HorseRideMoveToCommand::leave_() {
    HorseRideSetGearCommand::leave_();
}

void HorseRideMoveToCommand::loadParams_() {
    HorseRideSetGearCommand::loadParams_();
}

void HorseRideMoveToCommand::calc_() {
    HorseRideSetGearCommand::calc_();
}

bool HorseRideMoveToCommand::m32(ksys::act::Actor* actor) {
    _98.x(*mTargetPos_d);
    if (!_98.sub_710070DC38(actor, true))
        return false;
    return HorseRideSetGearCommand::m32(actor);
}

}  // namespace uking::action
