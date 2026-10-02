#include "Game/AI/Action/actionHorseRideMoveToCommand.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseRideMoveToCommand::HorseRideMoveToCommand(const InitArg& arg) : HorseRideMoveCommand(arg) {}

HorseRideMoveToCommand::~HorseRideMoveToCommand() = default;

bool HorseRideMoveToCommand::init_(sead::Heap* heap) {
    return HorseRideMoveCommand::init_(heap);
}

void HorseRideMoveToCommand::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideMoveCommand::enter_(params);
}

void HorseRideMoveToCommand::leave_() {
    HorseRideMoveCommand::leave_();
}

void HorseRideMoveToCommand::loadParams_() {
    HorseRideMoveCommand::loadParams_();
}

void HorseRideMoveToCommand::calc_() {
    HorseRideMoveCommand::calc_();
}

bool HorseRideMoveToCommand::m32(ksys::act::Actor* actor) {
    _98.x(*mTargetPos_d);
    if (!_98.sub_710070DC38(actor, true))
        return false;
    return HorseRideMoveCommand::m32(actor);
}

}  // namespace uking::action
