#include "Game/AI/Behavior/behaviorCutGrass.h"

namespace uking::behavior {

CutGrass::CutGrass(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

CutGrass::~CutGrass() = default;

bool CutGrass::m6(sead::Heap* heap) {
    return true;
}

void CutGrass::m8() {}

void CutGrass::m9() {}

void CutGrass::loadParams() {
    getStaticParam(&mCutRange_s, "CutRange");
    getStaticParam(&mIntensity_s, "Intensity");
    getStaticParam(&mIsCallEffect_s, "IsCallEffect");
}

}  // namespace uking::behavior
