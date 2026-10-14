#include "Game/Actor/Action/actionForkHoverKeepRotateTurn.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkHoverKeepRotateTurn::ForkHoverKeepRotateTurn(const InitArg& arg)
    : ForkKeepRotateTurn(arg) {}

ForkHoverKeepRotateTurn::~ForkHoverKeepRotateTurn() = default;

bool ForkHoverKeepRotateTurn::init_(sead::Heap* heap) {
    return ForkKeepRotateTurn::init_(heap);
}

void ForkHoverKeepRotateTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkKeepRotateTurn::enter_(params);
    _68.changeMotionType(mActor->getCharacterController(), ksys::act::MotionType::Hover);
}

void ForkHoverKeepRotateTurn::leave_() {
    auto* actor = mActor;
    _68.resetRigidBodyMotion(actor);
    _68.resetMotionType(actor->getCharacterController());
    ForkKeepRotateTurn::leave_();
}

void ForkHoverKeepRotateTurn::loadParams_() {
    ForkKeepRotateTurn::loadParams_();
}

void ForkHoverKeepRotateTurn::calc_() {
    ForkKeepRotateTurn::calc_();
}

}  // namespace uking::action
