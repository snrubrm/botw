#include "Game/AI/Behavior/behaviorAnimalNeckRotate.h"

namespace uking::behavior {

AnimalNeckRotate::AnimalNeckRotate(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

AnimalNeckRotate::~AnimalNeckRotate() = default;

bool AnimalNeckRotate::m6(sead::Heap* heap) {
    return true;
}

void AnimalNeckRotate::loadParams() {
    getStaticParam(&mLimitAngleLR_s, "LimitAngleLR");
    getStaticParam(&mRotRate_s, "RotRate");
    getStaticParam(&mResetRotRate_s, "ResetRotRate");
    getStaticParam(&mIsUseParentRotOffset_s, "IsUseParentRotOffset");
}

}  // namespace uking::behavior
