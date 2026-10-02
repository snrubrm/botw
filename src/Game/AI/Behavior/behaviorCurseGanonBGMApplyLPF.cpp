#include "Game/AI/Behavior/behaviorCurseGanonBGMApplyLPF.h"

namespace uking::behavior {

CurseGanonBGMApplyLPF::CurseGanonBGMApplyLPF(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

CurseGanonBGMApplyLPF::~CurseGanonBGMApplyLPF() = default;

bool CurseGanonBGMApplyLPF::m6(sead::Heap* heap) {
    return true;
}

void CurseGanonBGMApplyLPF::loadParams() {
    getStaticParam(&mLPF_s, "LPF");
}

}  // namespace uking::behavior
