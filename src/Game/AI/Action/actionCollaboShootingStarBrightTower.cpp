#include "Game/AI/Action/actionCollaboShootingStarBrightTower.h"
#include <codec/seadHashCRC32.h>

namespace uking::action {

CollaboShootingStarBrightTower::CollaboShootingStarBrightTower(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CollaboShootingStarBrightTower::~CollaboShootingStarBrightTower() = default;

bool CollaboShootingStarBrightTower::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CollaboShootingStarBrightTower::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CollaboShootingStarBrightTower::leave_() {
    _28.fadeXLink();
}

void CollaboShootingStarBrightTower::loadParams_() {
    getAITreeVariable(&mCollaboShootingStarId_a, "CollaboShootingStarId");
    const sead::SafeString id = mCollaboShootingStarId_a->cstr();
    _50 = id;
    _48 = sead::HashCRC32::calcStringHash(id.cstr());
}

void CollaboShootingStarBrightTower::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
