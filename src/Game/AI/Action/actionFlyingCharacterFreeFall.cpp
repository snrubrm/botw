#include "Game/AI/Action/actionFlyingCharacterFreeFall.h"
#include "KingSystem/ActorSystem/actUnk_71007A24BC.h"

namespace uking::action {

FlyingCharacterFreeFall::FlyingCharacterFreeFall(const InitArg& arg)
    : FlyingCharacterReaction(arg) {}

FlyingCharacterFreeFall::~FlyingCharacterFreeFall() = default;

bool FlyingCharacterFreeFall::init_(sead::Heap* heap) {
    return FlyingCharacterReaction::init_(heap);
}

void FlyingCharacterFreeFall::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterReaction::enter_(params);
    playAS("Fall", false, 0, 0, -1.0f);
}

void FlyingCharacterFreeFall::leave_() {
    FlyingCharacterReaction::leave_();
}

void FlyingCharacterFreeFall::loadParams_() {
    FlyingCharacterReaction::loadParams_();
}

void FlyingCharacterFreeFall::calc_() {
    FlyingCharacterReaction::calc_();
    if (isFinished() || isFailed())
        return;
    if (ksys::act::sub_71007A4864(mActor, false))
        setFinished();
}

bool FlyingCharacterFreeFall::isFinished() const {
    if (ActionBase::isFinished())
        return true;
    return ksys::act::sub_71007A4864(mActor, false);
}

}  // namespace uking::action
