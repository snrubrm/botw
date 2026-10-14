#include "Game/Actor/Action/actionFlyingCharacterDie.h"
#include "Game/Actor/aiUnk_710072BA90.h"

namespace uking::action {

FlyingCharacterDie::FlyingCharacterDie(const InitArg& arg) : FlyingActorDamageBase(arg) {}

bool FlyingCharacterDie::init_(sead::Heap* heap) {
    return FlyingActorDamageBase::init_(heap);
}

void FlyingCharacterDie::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingActorDamageBase::enter_(params);
    sub_710072BB28(mActor);
}

void FlyingCharacterDie::leave_() {
    FlyingActorDamageBase::leave_();
}

void FlyingCharacterDie::loadParams_() {
    FlyingActorDamageBase::loadParams_();
}

void FlyingCharacterDie::calc_() {
    FlyingActorDamageBase::calc_();
}

}  // namespace uking::action
