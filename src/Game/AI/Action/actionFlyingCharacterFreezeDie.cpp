#include "Game/AI/Action/actionFlyingCharacterFreezeDie.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

FlyingCharacterFreezeDie::FlyingCharacterFreezeDie(const InitArg& arg)
    : FlyingCharacterFreeze(arg) {}

FlyingCharacterFreezeDie::~FlyingCharacterFreezeDie() = default;

bool FlyingCharacterFreezeDie::init_(sead::Heap* heap) {
    return FlyingCharacterFreeze::init_(heap);
}

void FlyingCharacterFreezeDie::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterFreeze::enter_(params);
    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (auto* unit = sead::DynamicCast<uking::act::Unk_710244dd20>(actor->m159()))
            unit->_38 = 0.0f;
    }
}

void FlyingCharacterFreezeDie::leave_() {
    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (auto* unit = sead::DynamicCast<uking::act::Unk_710244dd20>(actor->m159()))
            unit->_38 = 1.0f;
    }
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
    if (isLandedMaybe(actor, false))
        return true;
    return isBgGroundHit(actor, false);
}

}  // namespace uking::action
