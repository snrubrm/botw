#include "Game/AI/Action/actionCollaboShootingStartFlying.h"
#include <codec/seadHashCRC32.h>

namespace uking::action {

CollaboShootingStartFlying::CollaboShootingStartFlying(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CollaboShootingStartFlying::~CollaboShootingStartFlying() = default;

bool CollaboShootingStartFlying::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CollaboShootingStartFlying::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CollaboShootingStartFlying::leave_() {
    ksys::act::ai::Action::leave_();
}

void CollaboShootingStartFlying::loadParams_() {
    getStaticParam(&mInitialVelocityMax_s, "InitialVelocityMax");
    getStaticParam(&mInitialVelocityMin_s, "InitialVelocityMin");
    getStaticParam(&mLookSuccessRate_s, "LookSuccessRate");
    getAITreeVariable(&mCollaboShootingStarId_a, "CollaboShootingStarId");
    const sead::SafeString id = mCollaboShootingStarId_a->cstr();
    _48 = id;
    _40 = sead::HashCRC32::calcStringHash(id.cstr());
}

void CollaboShootingStartFlying::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
