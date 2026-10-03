#include "Game/AI/Action/actionForkHoverKeepRotateTurnBase.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkHoverKeepRotateTurnBase::ForkHoverKeepRotateTurnBase(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkHoverKeepRotateTurnBase::~ForkHoverKeepRotateTurnBase() = default;

bool ForkHoverKeepRotateTurnBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkHoverKeepRotateTurnBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    const f32 angular_speed = actor->getAngVelocity().length();
    _5c.value = angular_speed;
    _5c.prev_value = angular_speed;
    sub_710073FA90(&_38, actor);
    mFlags.set(Flag::Changeable);
}

void ForkHoverKeepRotateTurnBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkHoverKeepRotateTurnBase::loadParams_() {
    getStaticParam(&mMinRotSpd_s, "MinRotSpd");
    getStaticParam(&mEndAngle_s, "EndAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ForkHoverKeepRotateTurnBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
