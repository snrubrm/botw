#include "Game/AI/Action/actionForkKeepRotateTurn.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkKeepRotateTurn::ForkKeepRotateTurn(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkKeepRotateTurn::~ForkKeepRotateTurn() = default;

bool ForkKeepRotateTurn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkKeepRotateTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    const f32 angular_speed = actor->getAngVelocity().length();
    _5c.value = angular_speed;
    _5c.prev_value = angular_speed;
    sub_710073FA90(&_38, actor);
    mFlags.set(Flag::Changeable);
}

void ForkKeepRotateTurn::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkKeepRotateTurn::loadParams_() {
    getStaticParam(&mMinRotSpd_s, "MinRotSpd");
    getStaticParam(&mEndAngle_s, "EndAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ForkKeepRotateTurn::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
