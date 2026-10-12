#include "Game/AI/Action/actionSmallDamageBackwardBase.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

SmallDamageBackwardBase::SmallDamageBackwardBase(const InitArg& arg) : KnockBackHitImpactForce(arg) {}

SmallDamageBackwardBase::~SmallDamageBackwardBase() = default;

bool SmallDamageBackwardBase::init_(sead::Heap* heap) {
    return KnockBackHitImpactForce::init_(heap);
}

void SmallDamageBackwardBase::enter_(ksys::act::ai::InlineParamPack* params) {
    KnockBackHitImpactForce::enter_(params);
    _90.set(-_68.value.x, 0.0f, -_68.value.z);
    _90.normalize();
}

void SmallDamageBackwardBase::leave_() {
    KnockBackHitImpactForce::leave_();
}

void SmallDamageBackwardBase::loadParams_() {
    KnockBackHitImpactForce::loadParams_();
}

void SmallDamageBackwardBase::calc_() {
    KnockBackHitImpactForce::calc_();
    sub_710073FA94(&_9c, mActor);
    sub_71007407F0(&_9c, _90, getUpDir(mActor), true, sead::Mathf::deg2rad(30.0f));
    sub_7100740F1C(_9c, mActor);
}

void SmallDamageBackwardBase::m34() {
    _90.set(-_68.value.x, 0.0f, -_68.value.z);
    _90.normalize();
}

}  // namespace uking::action
