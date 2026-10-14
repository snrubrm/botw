#include "Game/Actor/Action/actionFlyingBirdDie.h"
#include "Game/Actor/aiUnk_710072BA90.h"

namespace uking::action {

FlyingBirdDie::FlyingBirdDie(const InitArg& arg) : FlyingActorDamageBase(arg) {}

FlyingBirdDie::~FlyingBirdDie() = default;

bool FlyingBirdDie::init_(sead::Heap* heap) {
    return FlyingActorDamageBase::init_(heap);
}

void FlyingBirdDie::enter_(ksys::act::ai::InlineParamPack* params) {
    _108 = ksys::Timer(*mEnableHitGroundCheckTimer_s, *mEnableHitGroundCheckTimer_s);
    _114 = false;
    FlyingActorDamageBase::enter_(params);
    sub_710072BB28(mActor);
}

void FlyingBirdDie::leave_() {
    FlyingActorDamageBase::leave_();
}

void FlyingBirdDie::loadParams_() {
    FlyingActorDamageBase::loadParams_();
    getStaticParam(&mEnableHitGroundCheckTimer_s, "EnableHitGroundCheckTimer");
    getStaticParam(&mIsChangeStateFallOnce_s, "IsChangeStateFallOnce");
}

void FlyingBirdDie::calc_() {
    FlyingActorDamageBase::calc_();
}

void FlyingBirdDie::m32() {
    if (*mIsChangeStateFallOnce_s)
        _114 = true;
}

bool FlyingBirdDie::m38() {
    if (_114 && _64)
        return true;

    if (_108.value <= sead::Mathf::epsilon())
        return FlyingCharacterFreeFallBase::m38();

    _108.update();
    if (_108.value <= sead::Mathf::epsilon())
        return FlyingCharacterFreeFallBase::m38();

    return false;
}

}  // namespace uking::action
