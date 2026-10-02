#include "Game/AI/Action/actionSmallDamageBackwardBase.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

SmallDamageBackwardBase::SmallDamageBackwardBase(const InitArg& arg) : TakeHitImpactForce(arg) {}

SmallDamageBackwardBase::~SmallDamageBackwardBase() = default;

bool SmallDamageBackwardBase::init_(sead::Heap* heap) {
    return TakeHitImpactForce::init_(heap);
}

void SmallDamageBackwardBase::enter_(ksys::act::ai::InlineParamPack* params) {
    TakeHitImpactForce::enter_(params);
}

void SmallDamageBackwardBase::leave_() {
    TakeHitImpactForce::leave_();
}

void SmallDamageBackwardBase::loadParams_() {
    TakeHitImpactForce::loadParams_();
}

// NON_MATCHING: the original reuses the gravity stack slot for the normalized direction
void SmallDamageBackwardBase::calc_() {
    TakeHitImpactForce::calc_();
    sub_710073FA94(&_9c, mActor);
    sead::Vector3f gravity;
    sub_710072DC50(&gravity, mActor);
    sead::Vector3f up = -gravity;
    if (up.normalize() < sead::Mathf::epsilon())
        up.set(sead::Vector3f::ey);
    sub_71007407F0(&_9c, _90, up, true, sead::Mathf::deg2rad(30.0f));
    sub_7100740F1C(_9c, mActor);
}

void SmallDamageBackwardBase::m34() {
    _90.set(-_68.value.x, 0.0f, -_68.value.z);
    _90.normalize();
}

}  // namespace uking::action
