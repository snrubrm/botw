#include "Game/AI/Action/actionFlyingCharacterFreezeDie.h"
#include "KingSystem/ActorSystem/actUnk_71007A24BC.h"

namespace uking::action {

FlyingCharacterFreezeDie::FlyingCharacterFreezeDie(const InitArg& arg)
    : FlyingCharacterFreeze(arg) {}

FlyingCharacterFreezeDie::~FlyingCharacterFreezeDie() = default;

bool FlyingCharacterFreezeDie::init_(sead::Heap* heap) {
    return FlyingCharacterFreeze::init_(heap);
}

void FlyingCharacterFreezeDie::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterFreeze::enter_(params);
}

void FlyingCharacterFreezeDie::leave_() {
    FlyingCharacterFreeze::leave_();
}

void FlyingCharacterFreezeDie::loadParams_() {
    FlyingCharacterFreeze::loadParams_();
}

void FlyingCharacterFreezeDie::calc_() {
    FlyingCharacterFreeze::calc_();
}

bool FlyingCharacterFreezeDie::isFinished() const {
    auto* actor = mActor;
    if (ksys::act::sub_71007A4638(actor, false))
        return true;
    return ksys::act::sub_71007A4864(actor, false);
}

}  // namespace uking::action
