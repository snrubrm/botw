#include "Game/AI/AI/aiDrawnWeaponSelector.h"

namespace uking::ai {

DrawnWeaponSelector::DrawnWeaponSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DrawnWeaponSelector::~DrawnWeaponSelector() = default;

bool DrawnWeaponSelector::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool DrawnWeaponSelector::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool DrawnWeaponSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DrawnWeaponSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DrawnWeaponSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DrawnWeaponSelector::loadParams_() {}

}  // namespace uking::ai
