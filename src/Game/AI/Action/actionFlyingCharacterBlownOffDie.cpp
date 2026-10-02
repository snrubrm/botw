#include "Game/AI/Action/actionFlyingCharacterBlownOffDie.h"

namespace uking::action {

FlyingCharacterBlownOffDie::FlyingCharacterBlownOffDie(const InitArg& arg)
    : FlyingCharacterBlownOff(arg) {}

FlyingCharacterBlownOffDie::~FlyingCharacterBlownOffDie() = default;

bool FlyingCharacterBlownOffDie::init_(sead::Heap* heap) {
    return FlyingCharacterBlownOff::init_(heap);
}

void FlyingCharacterBlownOffDie::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyingCharacterBlownOff::enter_(params);
}

void FlyingCharacterBlownOffDie::leave_() {
    FlyingCharacterBlownOff::leave_();
}

void FlyingCharacterBlownOffDie::loadParams_() {
    FlyingCharacterBlownOff::loadParams_();
}

void FlyingCharacterBlownOffDie::calc_() {
    FlyingCharacterBlownOff::calc_();
}

void FlyingCharacterBlownOffDie::m35() {
    playAS("LargeDamage", false, 0, 0, -1.0f);
}

}  // namespace uking::action
