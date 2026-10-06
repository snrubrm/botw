#include "Game/AI/Action/actionGuardianChargeBeam.h"
#include <random/seadGlobalRandom.h>
#include "Game/DLC/aocHardModeManager.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

GuardianChargeBeam::GuardianChargeBeam(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GuardianChargeBeam::~GuardianChargeBeam() = default;

bool GuardianChargeBeam::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GuardianChargeBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    _48 = 0;
    _4c = *mTime_s;
    if (auto* manager = aoc::HardModeManager::instance()) {
        if (manager->checkFlag(aoc::HardModeManager::Flag::EnableHardMode) &&
            manager->isHardModeChangeOn(
                aoc::HardModeManager::HardModeChange::RandomizeGuardianChargeBeam)) {
            if (sead::GlobalRandom::instance()->getU32(5) == 0)
                _4c += *mTimeRand_s;
        }
    }
}

void GuardianChargeBeam::leave_() {
    ksys::act::ai::Action::leave_();
}

void GuardianChargeBeam::loadParams_() {
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mTimeRand_s, "TimeRand");
    getStaticParam(&mChargeRadius_s, "ChargeRadius");
    getStaticParam(&mColor_s, "Color");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: only the final bool tests differ (target: tbnz / cbz on the two chase paths, ours: cbnz / tbz)
void GuardianChargeBeam::calc_() {
    if (ksys::VFR::chase(&_48, _4c))
        setFinished();
}

}  // namespace uking::action
