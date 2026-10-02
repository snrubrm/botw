#include "Game/AI/Action/actionForkAlwaysRotate.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
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
    if (*mOnEndForceStop_s)
        ksys::act::sub_7100EE5A14(mActor, sead::Vector3f::zero);
}

void ForkAlwaysRotate::loadParams_() {
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mOnEndForceStop_s, "OnEndForceStop");
    getStaticParam(&mRotAxis_s, "RotAxis");
}

void ForkAlwaysRotate::calc_() {
    const f32 max_speed = sead::Mathf::max(*mRotSpd_s, _38.value);
    _38.lerp(*mRotSpd_s, 0.12f, max_speed * 0.2f, max_speed * 0.05f);
    _38.updateStats();
    ksys::act::sub_7100EE5A14(mActor, *mRotAxis_s * _38.value);
}

}  // namespace uking::action
