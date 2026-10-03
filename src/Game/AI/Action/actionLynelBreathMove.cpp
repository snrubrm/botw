#include "Game/AI/Action/actionLynelBreathMove.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
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
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    _28.sub_7100716408(pos);
    ksys::act::sub_7100EE5980(mActor, _1c);
    _d0 = false;
}

}  // namespace uking::action
