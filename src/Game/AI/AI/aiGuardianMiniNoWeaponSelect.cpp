#include "Game/AI/AI/aiGuardianMiniNoWeaponSelect.h"

namespace uking::ai {

GuardianMiniNoWeaponSelect::GuardianMiniNoWeaponSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

GuardianMiniNoWeaponSelect::~GuardianMiniNoWeaponSelect() = default;

void GuardianMiniNoWeaponSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool GuardianMiniNoWeaponSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool GuardianMiniNoWeaponSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool GuardianMiniNoWeaponSelect::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void GuardianMiniNoWeaponSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianMiniNoWeaponSelect::loadParams_() {
    getStaticParam(&mIsSelectFirstTime_s, "IsSelectFirstTime");
}

}  // namespace uking::ai
