#include "Game/AI/Action/actionFlyingCharacterFreeFallEx.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

FlyingCharacterFreeFallEx::FlyingCharacterFreeFallEx(const InitArg& arg)
    : FlyingCharacterFreeFall(arg) {}

FlyingCharacterFreeFallEx::~FlyingCharacterFreeFallEx() = default;

bool FlyingCharacterFreeFallEx::init_(sead::Heap* heap) {
    return FlyingCharacterFreeFall::init_(heap);
}

void FlyingCharacterFreeFallEx::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterFreeFall::enter_(params);
    if (auto* cc = mActor->getCharacterController()) {
        _78 = cc->get110();
        cc->sub_7100F5EEB8(*mGravityScaleRate_s);
    }
}

void FlyingCharacterFreeFallEx::leave_() {
    FlyingCharacterFreeFall::leave_();
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5EEB8(_78);
}

void FlyingCharacterFreeFallEx::loadParams_() {
    FlyingCharacterFreeFall::loadParams_();
    getStaticParam(&mGravityScaleRate_s, "GravityScaleRate");
}

void FlyingCharacterFreeFallEx::calc_() {
    FlyingCharacterFreeFall::calc_();
}

}  // namespace uking::action
