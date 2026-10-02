#include "Game/AI/Action/actionForkAlwaysRotate.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkAlwaysRotate::ForkAlwaysRotate(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAlwaysRotate::~ForkAlwaysRotate() = default;

bool ForkAlwaysRotate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAlwaysRotate::enter_(ksys::act::ai::InlineParamPack* params) {
    const f32 speed = mActor->getAngVelocity().length();
    _38.value = speed;
    _38.prev_value = speed;
    mFlags.set(Flag::Changeable);
}

void ForkAlwaysRotate::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkAlwaysRotate::loadParams_() {
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mOnEndForceStop_s, "OnEndForceStop");
    getStaticParam(&mRotAxis_s, "RotAxis");
}

void ForkAlwaysRotate::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
