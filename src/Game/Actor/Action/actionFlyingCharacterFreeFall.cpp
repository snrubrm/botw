#include "Game/Actor/Action/actionFlyingCharacterFreeFall.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

FlyingCharacterFreeFall::FlyingCharacterFreeFall(const InitArg& arg)
    : FlyingCharacterFreeFallBase(arg) {}

FlyingCharacterFreeFall::~FlyingCharacterFreeFall() = default;

bool FlyingCharacterFreeFall::init_(sead::Heap* heap) {
    return FlyingCharacterFreeFallBase::init_(heap);
}

void FlyingCharacterFreeFall::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterFreeFallBase::enter_(params);
    playAS("Fall", false, 0, 0, -1.0f);
}

void FlyingCharacterFreeFall::leave_() {
    FlyingCharacterFreeFallBase::leave_();
}

void FlyingCharacterFreeFall::loadParams_() {
    FlyingCharacterFreeFallBase::loadParams_();
}

void FlyingCharacterFreeFall::calc_() {
    FlyingCharacterFreeFallBase::calc_();
    if (isFinished() || isFailed())
        return;
    if (isBgGroundHit(mActor, false))
        setFinished();
}

bool FlyingCharacterFreeFall::isFinished() const {
    if (ActionBase::isFinished())
        return true;
    return isBgGroundHit(mActor, false);
}

}  // namespace uking::action
