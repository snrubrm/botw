#include "Game/AI/Action/actionForkAlwaysTargetVerticalRotate.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::action {

ForkAlwaysTargetVerticalRotate::ForkAlwaysTargetVerticalRotate(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkAlwaysTargetVerticalRotate::~ForkAlwaysTargetVerticalRotate() = default;

bool ForkAlwaysTargetVerticalRotate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAlwaysTargetVerticalRotate::enter_(ksys::act::ai::InlineParamPack* params) {
    const f32 speed = mActor->getAngVelocity().length();
    _50.value = _50.prev_value = speed;
    _5c.set(*mTargetPos_d);
    mFlags.set(Flag::Changeable);
}

void ForkAlwaysTargetVerticalRotate::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkAlwaysTargetVerticalRotate::loadParams_() {
    getStaticParam(&mRotSpdMax_s, "RotSpdMax");
    getStaticParam(&mRotSpdRatio_s, "RotSpdRatio");
    getStaticParam(&mIsUpdateTargetPos_s, "IsUpdateTargetPos");
    getStaticParam(&mIsIgnoreY_s, "IsIgnoreY");
    getStaticParam(&mOtherAxis_s, "OtherAxis");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: the original loads the target position before the actor's translation and the cross
// product products in another order (load scheduling)
void ForkAlwaysTargetVerticalRotate::calc_() {
    _50.lerp(*mRotSpdMax_s, *mRotSpdRatio_s, *mRotSpdMax_s * 0.1f, *mRotSpdMax_s * 0.03f);
    _50.updateStats();

    const sead::Vector3f& target = *mIsUpdateTargetPos_s ? *mTargetPos_d : _5c;
    sead::Vector3f dir = target - mActor->getMtx().getTranslation();
    if (*mIsIgnoreY_s)
        dir.y = 0;
    dir.normalize();
    const sead::Vector3f ang_vel = dir.cross(*mOtherAxis_s) * _50.value;
    ksys::act::sub_7100EE5A14(mActor, ang_vel);
}

}  // namespace uking::action
