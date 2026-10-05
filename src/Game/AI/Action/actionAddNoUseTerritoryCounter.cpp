#include "Game/AI/Action/actionAddNoUseTerritoryCounter.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>

namespace uking::action {

// NON_MATCHING: x9 / x10 swapped (register allocation of the actor and -1 temporaries)
AddNoUseTerritoryCounter::AddNoUseTerritoryCounter(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

AddNoUseTerritoryCounter::~AddNoUseTerritoryCounter() = default;

bool AddNoUseTerritoryCounter::init_(sead::Heap* heap) {
    *mIsUseTerritory_a = false;
    const int counter = *mCounter_s;
    _40._0 = 0;
    const int scaled = counter * 1.1f;
    _40._18 = sead::Mathi::min(counter, scaled);
    _40._1c = sead::Mathi::max(counter, scaled);
    if (*mCamDist_s > 0.0f)
        _40._14 = *mCamDist_s;
    return true;
}

void AddNoUseTerritoryCounter::enter_(ksys::act::ai::InlineParamPack* params) {
    if (isRootAiParamINot5()) {
        const int lower = _40._18;
        const int upper = _40._1c;
        _40._10 = lower == upper ? lower : sead::GlobalRandom::instance()->getS32Range(lower, upper);
        if (_40._0 == 2)
            _40._0 = 0;
        if (*mTerritoryArea_m > 0)
            *mIsUseTerritory_a = true;
    }
    mFlags.set(Flag::Changeable);
}

void AddNoUseTerritoryCounter::leave_() {
    ksys::act::ai::Action::leave_();
}

void AddNoUseTerritoryCounter::loadParams_() {
    getStaticParam(&mCounter_s, "Counter");
    getStaticParam(&mCamDist_s, "CamDist");
    getMapUnitParam(&mTerritoryArea_m, "TerritoryArea");
    getAITreeVariable(&mIsUseTerritory_a, "IsUseTerritory");
}

void AddNoUseTerritoryCounter::calc_() {
    if (*mIsUseTerritory_a) {
        const f32 prev = _40._10;
        _40.sub_7100709414();
        if (!(prev < 0.0f) && _40._10 < 0.0f)
            *mIsUseTerritory_a = false;
    }
}

}  // namespace uking::action
