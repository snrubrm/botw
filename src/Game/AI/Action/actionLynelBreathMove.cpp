#include "Game/AI/Action/actionLynelBreathMove.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

LynelBreathMove::LynelBreathMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LynelBreathMove::~LynelBreathMove() = default;

bool LynelBreathMove::init_(sead::Heap* heap) {
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000);
    return true;
}

void LynelBreathMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LynelBreathMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void LynelBreathMove::loadParams_() {}

void LynelBreathMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
