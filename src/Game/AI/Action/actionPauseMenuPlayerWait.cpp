#include "Game/AI/Action/actionPauseMenuPlayerWait.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PauseMenuPlayerWait::PauseMenuPlayerWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PauseMenuPlayerWait::~PauseMenuPlayerWait() = default;

bool PauseMenuPlayerWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PauseMenuPlayerWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PauseMenuPlayerWait::leave_() {
    ksys::act::ai::Action::leave_();
}

void PauseMenuPlayerWait::loadParams_() {}

void PauseMenuPlayerWait::calc_() {
    mActor->x_22(sead::Vector3f::zero, sead::Vector3f::zero);
}

}  // namespace uking::action
